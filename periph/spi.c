/**
 * @file spi.c
 * @author Tomás Herrera - <taherrera@uc.cl>
 *
 * @brief Uses spidev as SPI interface.
 *
 * Requires an SPI Kernel driver be loaded to expose a /dev/spidevX.Y
 * interface and an AD7390 be connected on the SPI bus.
 * 
 * Uses SPI0_D0 (pin 21) as MISO (input to BBB) and SPIO_D1 (pin 18) as MOSI
 *
 */

 
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <time.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/ioctl.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "spi.h"

#define UENVDIR "/boot/uEnv.txt"
#define ENABLESPI "capemgr.enable_partno=BB-SPI0-01"
//#define DEBUG

static int spidev_fd;
static char device[] = "/dev/spidev%d.0"; 
static struct spi_ioc_transfer tr;
static spi_mode_t spi_mode;
static int ret;

void spi_init(spi_t bus)
{

	char buff[30];
	sprintf(buff, device, bus);
	spidev_fd = open(buff,O_RDWR);
	if (spidev_fd < 0)
		printf("[spi.c] Error opening spidev_fd !\n");
	tr.delay_usecs = 0;
	tr.bits_per_word = 8;
	#ifdef DEBUG
	printf("[spi.c] spidev_fd = %d\n",spidev_fd);
	#endif
	return;
}

void spi_init_pins(spi_t bus)
{
	(void) bus;
	return;
}

int spi_init_cs(spi_t bus, spi_cs_t cs)
{
	(void) bus;
	(void) cs;
	return 1;

}

int spi_acquire(spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
{
	(void) bus;
	(void) cs;
	if (mode == (spi_mode_t) SPI_MODE0)
	{
		spi_mode = SPI_MODE_0;
	}else if(mode == (spi_mode_t) SPI_MODE1)
        { 
		spi_mode = SPI_MODE_1;
        }else if(mode == (spi_mode_t) SPI_MODE2)
        { 
		spi_mode = SPI_MODE_2;
        }else if(mode == (spi_mode_t) SPI_MODE3)
        { 
		spi_mode = SPI_MODE_3;
        }else{
		error(1,1,"[spi.c] SPI mode %d not defined\n",spi_mode);
	}

	/*
	 * Set SPI mode
	 */
	ret = ioctl(spidev_fd , SPI_IOC_WR_MODE, &spi_mode);
	if (ret == -1)
		printf("[spi.c] can't set spi mode\n");

	ret = ioctl(spidev_fd , SPI_IOC_RD_MODE, &spi_mode);
	if (ret == -1)
		printf("[spi.c] can't get spi mode\n");

	tr.speed_hz = clk;
	return 0;


}

void spi_release(spi_t bus)
{
	(void) bus;
	return;
}

uint8_t spi_transfer_byte(spi_t bus, spi_cs_t cs, bool cont, uint8_t out)
{
	(void) bus;
	(void) cs;
	(void) cont;

	tr.len = 1;
        tr.tx_buf = (uint32_t) &out;
	uint8_t inbuf;
	tr.rx_buf = (uint32_t) &inbuf;

        ret = ioctl(spidev_fd, SPI_IOC_MESSAGE(2), &tr);

        if (ret < 1){
                printf("[spi.c] can't send spi message");
        }

	return (uint8_t) inbuf;
}


void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont, const void *out, void *in, size_t len)
{

	tr.tx_buf = (const uint32_t) out;

	/* ioctl copies len bytes into rx_buf,
         * and sizeof(in) could be len -1
	 * so we need an auxin buffer */
	uint8_t auxin[2048];
	tr.rx_buf = (uint32_t) auxin;

	tr.len = len;
	#ifdef DEBUG
	printf("[spi.c] Making Transfer with fd: %d, %d bits \n",spidev_fd,tr.bits_per_word);
	#endif
	/* Make a Transfer */
	ret = ioctl(spidev_fd, SPI_IOC_MESSAGE(3), &tr);

	if (ret == 1){
		error(1,1,"[spi.c] ERROR can't send spi message");
	}
	#ifdef DEBUG
	printf("[spi.c] ret: %d\n", ret);
	printf("[spi.c] Mem moving \n");
	#endif
	/* The first byte read is always 0, correct this */
	memmove(in, auxin + 1,sizeof in - sizeof *in);

}


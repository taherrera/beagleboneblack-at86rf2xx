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

static int spidev_fd;
static char device[] = "/dev/spidev%d.0"; 
static struct spi_ioc_transfer tr;
static spi_mode_t spi_mode;

void spi_init(spi_t bus)
{

	char buff[30];
	sprintf(buff, device, bus);
	spidev_fd = open(buff,O_RDWR);
	tr.delay_usecs = 0;
        tr.bits_per_word = 8;
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
	spi_mode = mode;
	tr.speed_hz = clk;
	return 1;

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
	int ret;
        int out_fd;
	
        tr.tx_buf = (uint32_t) &out;

        ret = ioctl(spidev_fd, SPI_IOC_MESSAGE(2), &tr);

        if (ret < 1){
                error("can't send spi message");
        }

	return (uint8_t) ret;
}


void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont, const void *out, void *in, size_t len)
{
	int ret;
	int out_fd;
	tr.tx_buf = (const uint32_t) out;
	tr.rx_buf = (uint32_t) in;
	tr.len = len;

	ret = ioctl(spidev_fd, SPI_IOC_MESSAGE(2), &tr);

	if (ret < 1){
		error("can't send spi message");
	}

	memset(in, tr.rx_buf, sizeof(tr.rx_buf));

}


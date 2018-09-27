/**
 * @file spi_ad7390.c
 * @author Alex Hiam - <alex@graycat.io>
 * @author Tomás Herrera - <taherrera@uc.cl>
 *
 * @brief Uses serbus as SPI interface.
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

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static uint8_t running;
static int spidev_fd;

int SPI_setMaxFrequency(int spidev_fd, uint32_t frequency) {
  if (ioctl(spidev_fd, SPI_IOC_WR_MAX_SPEED_HZ, &frequency) < 0) return -1;
  return 0;
}

/**
 * @brief Sets the given SPI bus per the AD7390's required configuration
 *
 * @param spi_fd SPI bus file descriptor
 */
void spi_init(spi_t bus) {

  // TODO: change file descriptor for spi_t
  SPI_setMaxFrequency(spi_fd, AD7390_FREQ);
  SPI_setBitsPerWord(spi_fd, AD7390_BITS);
  SPI_setClockMode(spi_fd, AD7390_CLOCKMODE);
  SPI_setCSActiveHigh(spi_fd);
  SPI_setBitOrder(spi_fd, SPI_MSBFIRST);
}

/**
 * @brief Sets the output of the AD7390 in the range 0-4095
 *
 * @param spi_fd SPI bus file descriptor
 * @param value DAC value in range 0-4095
 */
void AD7390_setValue(int spi_fd, uint16_t value) {
  SPI_write(spi_fd, (void*) &value, 1);
}




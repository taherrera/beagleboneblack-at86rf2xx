
#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>


int main() {
	/* Before starting, initialize SPI */
	spi_init(SPI_BUS);
	spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);

	//reg_read(AT86RF2XX_REG__PHY_TX_PWR); /* Segmentation Fault */
	printf("TX_PWR: %d\n",get_txpwr());
	printf("Channel: %d\n", get_chan());
	printf("Long Addr: %d, Short Addr: %d\n", get_addr_long(), get_addr_short());

	return 1;
}


#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>

#define INTGPIO 48
#define SLEEPGPIO 49
#define RESETGPIO 60
#define CSGPIO 17 /* Not movable */

int main() {
	//spi_init(SPI_BUS);
        //spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);
	//reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
	//assert_awake();
	/* Before starting, initialize */
	init(CSGPIO, INTGPIO, SLEEPGPIO, RESETGPIO);
	//spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);

	//reg_read(AT86RF2XX_REG__PHY_TX_PWR); /* Segmentation Fault */
	//printf("TX_PWR: %d\n",get_txpower());
	//printf("Channel: %d\n", get_chan());
	//printf("Long Addr: %d, Short Addr: %d\n", get_addr_long(), get_addr_short());

	return 1;
}
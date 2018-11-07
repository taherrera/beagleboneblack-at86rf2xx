
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

	

	return 1;
}

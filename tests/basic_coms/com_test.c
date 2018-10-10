#define SPI_BUS 1        // /dev/spidev1.x
#define SPI_CS 0         // /dev/spidevx.0
#define SPI_FREQ SPI_CLK_1MHZ // in Hz
#define CLOCKMODE 3      // 
#define CONT 0
 
#include "../../periph/spi.h"
#include "../../at86rf2xx/at86rf2xx-registers.h"

int main() {
	spi_init(SPI_BUS);
	spi_acquire(SPI_BUS, SPI_CS , CLOCKMODE, SPI_FREQ);
	const char outbuff[2] = {AT86RF2XX_REG__PART_NUM,AT86RF2XX_ACCESS_READ};
	char inbuff[1];
	spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
	printf("%c",*inbuff);
	return 1;
}

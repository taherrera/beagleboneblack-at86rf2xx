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
	const char outbuff_1[2] = {AT86RF2XX_REG__PART_NUM,AT86RF2XX_ACCESS_READ};
	char inbuff_1[1];
	spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff_1, (void*) inbuff_1, 2);
	printf("Partnum should be 0x0b (reset value), outputing: %x\n",*inbuff_1);
	const char outbuff_2[2] = {AT86RF2XX_REG__VERSION_NUM,AT86RF2XX_ACCESS_READ};
        char inbuff_2[1];
        spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff_2, (void*) inbuff_2, 2);
	printf("Version should be 0x01 (reset value), outputin: %x\n",*inbuff_2);
	return 1;
}

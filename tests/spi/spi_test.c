#define SPI_BUS 1        // /dev/spidev1.x
#define SPI_CS 0         // /dev/spidevx.0
#define SPI_FREQ SPI_CLK_1MHZ // in Hz
#define CLOCKMODE 3      // 
#define CONT 0
#define MESSAGE "@PQ"

#include "../../periph/spi.h"

int main() {
	spi_init(SPI_BUS);
	spi_acquire(SPI_BUS, SPI_CS , CLOCKMODE, SPI_FREQ);
	const char outbuff[4] = MESSAGE;
	char inbuff[2];
	spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, sizeof(MESSAGE));
	
}

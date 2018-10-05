#define SPI_BUS 1        // /dev/spidev1.x
#define SPI_CS 0         // /dev/spidevx.0
#define SPI_FREQ SPI_CLK_1MHZ // in Hz
#define CLOCKMODE 3      // 


#include "../../periph/spi.h"

int main() {
	spi_init(SPI_BUS);
	spi_acquire(SPI_BUS, SPI_CS , CLOCKMODE, SPI_FREQ);
	char outbuff[100];
	char inbuff[100];
	spi_transfer_bytes(SPI_BUS, SPI_CS, 0, (void*) outbuff, (void*) inbuff, 2);
	
}

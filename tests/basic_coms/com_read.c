#include "../../periph/spi.h"
#include "../../at86rf2xx/at86rf2xx-registers.h"


#define SPI_BUS 1        // /dev/spidev1.x
#define SPI_CS 0         // /dev/spidevx.0
#define SPI_FREQ SPI_CLK_1MHZ // in Hz
#define CLOCKMODE SPI_MODE0
#define CONT 0
#define MESSAGENUM 0

// Transfering bytes one by one does not work
// i.e. transferbyte(..) function
// Since running  SPI through userspace
// is too slow. :(
// Solution: use transferbytes(...) function.

#define TRANSFERBYTES

int main() {
	spi_init(SPI_BUS);
	spi_acquire(SPI_BUS, SPI_CS , CLOCKMODE, SPI_FREQ);
	char inbuff[2] = {0x00,0x00};
	uint8_t outstr;
	uint8_t byte0;
	uint8_t byte1;
	switch (MESSAGENUM){
		case 0:
			;
			byte0 = AT86RF2XX_REG__PART_NUM;
			byte1 = AT86RF2XX_ACCESS_READ;
			outstr = 0x0b;
			break;
		case 1:
			;
			byte0  = AT86RF2XX_REG__VERSION_NUM;
			byte1 = AT86RF2XX_ACCESS_READ;
			outstr = 0x01;
			break;
		case 2:
			;
			byte0 = AT86RF2XX_REG__PART_NUM;
			byte1 = AT86RF2XX_ACCESS_READ;
			outstr = 0x00; 
			break;
	}
	const char outbuff[2] = {AT86RF2XX_ACCESS_REG | byte0, byte1};
	#ifdef TRANSFERBYTES
	spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
	printf("Should be %x (reset value), outputing: %x, %x \n",outstr,inbuff[0],inbuff[1]);
	#else
	uint8_t out;
        spi_transfer_byte(SPI_BUS, SPI_CS, CONT, (uint8_t) outbuff[0]);
	out = spi_transfer_byte(SPI_BUS, SPI_CS, CONT, (uint8_t) outbuff[1]);
        printf("Should be %x (reset value), outputing: %x \n",outstr,out);
	#endif
	return 1;
}

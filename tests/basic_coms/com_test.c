#include "../../periph/spi.h"
#include "../../at86rf2xx/at86rf2xx-registers.h"


#define SPI_BUS 1        // /dev/spidev1.x
#define SPI_CS 0         // /dev/spidevx.0
#define SPI_FREQ SPI_CLK_1MHZ // in Hz
#define CLOCKMODE SPI_MODE0
#define CONT 0
#define MESSAGENUM 0


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

	//printf("Before output: %x, addr: %x\n", *inbuff, inbuff);
	spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
	printf("Partnum should be %x (reset value), outputing: %x, %x \n",outstr,inbuff[0],inbuff[1]);
	//const char outbuff_2[2] = {AT86RF2XX_ACCESS_READ,AT86RF2XX_REG__VERSION_NUM};
        //char inbuff_2[1] = {0};
        //spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff_2, (void*) inbuff_2, 2);
	//printf("Version should be 0x01 (reset value), outputin: %x\n",*inbuff_2);
	return 1;
}

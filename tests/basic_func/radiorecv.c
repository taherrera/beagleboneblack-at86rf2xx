
#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define INTGPIO 48
#define SLEEPGPIO 49
#define RESETGPIO 60
#define CSGPIO 17 /* Not movable */

int main() {
	//spi_init(SPI_BUS);
        //spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);
	//reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
	//assert_awake();



	printf("[radiorecv.c] Initializing device");

	/* Before starting, initialize */
	init(CSGPIO, INTGPIO, SLEEPGPIO, RESETGPIO);
	//spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);

	set_txpower(0);
	uint16_t power = get_txpower();
	printf("[radiosend.c] Tx radio power is %d dBm\n", power);

	set_chan(26);
	uint8_t channel = get_chan();
	printf("[radiorecv.c] Current radio channel is %d\n", channel);

	//const uint8_t sram_offset = 0x05;
	//uint8_t sram_data[5] = "hello";
	//sram_write(sram_offset, sram_data, 5);


	uint8_t trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
	printf("[radiorecv.c] TRX_STATUS: 0x%x \n", trx_status);

	uint8_t buf[255];

	printf("[radiorecv.c] Sending RX_START command\n");
	set_state(AT86RF2XX_TRX_STATUS__RX_ON);
	printf("[radiorecv.c] Sent RX_START command\n");
	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiorecv.c] RX_STATUS: 0x%x \n", trx_status);

	int i;
	while (trx_status == AT86RF2XX_TRX_STATUS__RX_ON){
		usleep(1000000);
		rx_read(buf, 127, 0);
		for (i=0;i<127;i++)
			printf("%x,", buf[i]);
		printf("\n");
		fflush(stdout);
	}
	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiorecv.c] TRX_STATUS: 0x%x \n", trx_status);
	sleep(1);
	return 0;
}

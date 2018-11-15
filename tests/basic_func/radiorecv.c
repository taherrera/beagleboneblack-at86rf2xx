
#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>
#include <unistd.h>

#define INTGPIO 48
#define SLEEPGPIO 49
#define RESETGPIO 60
#define CSGPIO 17 /* Not movable */

int main()
{

	printf("[radiosend.c] Initializing device");

	/* Before starting, initialize */
	init(CSGPIO, INTGPIO, SLEEPGPIO, RESETGPIO);
	//spi_acquire(SPI_BUS, SPI_CS, CLOCKMODE, SPI_FREQ);

	set_txpower(0);
	uint16_t power = get_txpower();
	printf("[radiosend.c] Tx radio power is %d dBm\n", power);

	set_chan(26);
	uint8_t channel = get_chan();
	printf("[radiosend.c] Current radio channel is %d\n", channel);

	//const uint8_t sram_offset = 0x05;
	//uint8_t sram_data[5] = "hello";
	//sram_write(sram_offset, sram_data, 5);
	//printf("[radiosend.c] Wrote to sram:  %s to address %d\n", sram_data, sram_offset);
	//uint8_t sram_buffer[5];
	//sram_read(sram_offset, sram_buffer, 5);
	//printf("[radiosend.c] Read from sram: %s from address %d\n", sram_buffer, sram_offset);


	uint8_t trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
	printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);

	printf("[radiosend.c] Sending RX_START command\n");
	set_state(AT86RF2XX_TRX_STATUS__RX_ON);
	printf("[radiosend.c] Sent RX_START command\n");
	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);

	while (trx_status == AT86RF2XX_TRX_STATUS__RX_ON)
		usleep(10000);

	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);
	sleep(1);
	return 0;
}

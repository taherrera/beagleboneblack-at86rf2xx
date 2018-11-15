
#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define INTGPIO 48
#define SLEEPGPIO 49
#define RESETGPIO 60
#define CSGPIO 17 /* Not movable */

int main()
{

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


	uint8_t trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
	printf("[radiorecv.c] TRX_STATUS: 0x%x \n", trx_status);

	printf("[radiosend.c] Sending RX_START command\n");
	set_state(AT86RF2XX_TRX_STATUS__RX_ON);
	printf("[radiorecv.c] Sent RX_START command\n");
	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiorecv.c] RX_STATUS: 0x%x \n", trx_status);

	//while (trx_status == AT86RF2XX_TRX_STATUS__RX_ON)
	//	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);

	//while (trx_status == AT86RF2XX_TRX_STATUS__BUSY_RX)
	//	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);

	uint8_t buf[2000];
	sleep(5);
	int i;
	printf("[radiorecv.c] Received something\n");
	rx_read(buf, 20, 0);
	printf("[radiorecv.c] Read from sram: %s\n ", buf);
	sleep(5);
	int recv_len = rx_len();
	printf("[radiorecv.c] Received len: %d\n",recv_len);
	rx_read(buf, recv_len, 0);
	printf("[radiorecv.c] Got buf\n");
	for (i=0;i<recv_len;i++)
		printf("%x,", buf[i]);
	printf("\n");
	fflush(stdout);

	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiorecv.c] TRX_STATUS: 0x%x \n", trx_status);
	return 0;
}

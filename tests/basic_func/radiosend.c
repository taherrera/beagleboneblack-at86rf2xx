
#include "../../at86rf2xx/at86rf2xx.h"
#include "../../periph/spi.h"
#include <stdio.h>
#include <unistd.h>

#define INTGPIO 48
#define SLEEPGPIO 49
#define RESETGPIO 60
#define CSGPIO 17 /* Not movable */

int main() {

	printf("[radiosend.c] Initializing device");

	/* Before starting, initialize */
	init(CSGPIO, INTGPIO, SLEEPGPIO, RESETGPIO);

	set_txpower(0);
	uint16_t power = get_txpower();
	printf("[radiosend.c] Tx radio power is %d dBm\n", power);

	set_chan(26);
	uint8_t channel = get_chan();
	printf("[radiosend.c] Current radio channel is %d\n", channel);

	uint8_t trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
	printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);

	uint8_t buf[20];
	/* Construct raw packet payload, length and FCS gets added in the chip */

	buf[0] = 0x21; /* Frame Control Field */
	buf[1] = 0xc8; /* Frame Control Field */
	buf[2] = 0x8b; /* Sequence number */
	buf[3] = 0xff; /* Destination PAN ID 0xffff */
	buf[4] = 0xff; /* Destination PAN ID */
	buf[5] = 0x30; /* Destination short address 0x0002 */
	buf[6] = 0x02; /* Destination short address */
	buf[7] = 0x23; /* Source PAN ID 0x0023 */
	buf[8] = 0x00; /* */
	buf[9] = 0x60; /* Source extended address ae:c2:4a:1c:21:16:e2:60 */
	buf[10] = 0xe2; /* */
	buf[11] = 0x16; /* */
	buf[12] = 0x21; /* */
	buf[13] = 0x1c; /* */
	buf[14] = 0x4a; /* */
	buf[15] = 0xc2; /* */
	buf[16] = 0xae; /* */
	buf[17] = 0xAA; /* Payload */
	buf[18] = 0xBB; /* */
	buf[19] = 0xCC; /* */


	//uint8_t loaded = tx_load(buf, sizeof(buf),0);
        //printf("[radiosend.c] %d bytes loaded into device \n", loaded);

	trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);

	//printf("[radiosend.c] Preparing TX\n");
	//tx_prepare();
	//printf("[radiosend.c] TX prepared\n");
	//trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        //printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);

	//printf("[radiosend.c] Sending TX_START command\n");
	//tx_exec();
	//printf("[radiosend.c] Sent TX_START command\n");
	//trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        //printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);
	//while (trx_status != AT86RF2XX_STATE_BUSY_TX_ARET)
	//	usleep(10000);
	//trx_status = reg_read(AT86RF2XX_REG__TRX_STATUS);
        //printf("[radiosend.c] TRX_STATUS: 0x%x \n", trx_status);
	printf("[radiosend.c] Send operation\n");
	send(buf,sizeof(buf));
	sleep(1);
	return 0;
}

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Brief example that demonstrates usage of the drivers
 *
 * @author      Tomás Herrera C. <taherrera@uc.cl>
 *
 * @}
 */

/*
 *  Connections:
 *  
 *   BBB          Extension Board  | (AT86RF2xx)
 *
 *  GPIO_60 (12)   --- 7 PWM(+)    | (8 RSTN) 
 *  GPIO_48 (15)   --- 9 IRQ/GPIO  | (24 IRQ)
 *  GPIO_49 (23)   --- 10          | (11 SLP_TR)
 *  SPIO_CSO (17)  --- 23 SPI_SS_A | (23 SEL)
 *  SPIO_D1 (18)   --- 16 SPI_MOSI | (22 MOSI)
 *  SPIO_DO (21)   --- 17 SPI_MISO | (20 MISO)
 *  SPIO_SLCK (22) --- 18 SPI_SCK  | (19 SCLK)
 *  
 *
*/

#include <sdio.h>
#include "at86rf2xx.h"

#define CHANNEL 26
#define RESET_GPIO 60
#define SLP_TR_GPIO 10
#define IRQ_GPIO 48
#define SEL_CS 0


void at86rf2xx_eventHandler() {
	/* One less event to handle! */
	at86rf2xx.events--;

	/* If transceiver is sleeping register access is impossible and frames are
	* lost anyway, so return immediately.
	*/
	byte state = at86rf2xx.get_status();
	if(state == AT86RF2XX_STATE_SLEEP)
		return;

	/* read (consume) device status */
	byte irq_mask = at86rf2xx.reg_read(AT86RF2XX_REG__IRQ_STATUS);

	/*  Incoming radio frame! */
	if (irq_mask & AT86RF2XX_IRQ_STATUS_MASK__RX_START)
		printf("[at86rf2xx] EVT - RX_START\n");

	/*  Done receiving radio frame; call our receive_data function.
	*/
	if (irq_mask & AT86RF2XX_IRQ_STATUS_MASK__TRX_END)
	{
		if(state == AT86RF2XX_STATE_RX_AACK_ON || state == AT86RF2XX_STATE_BUSY_RX_AACK) 
		{
			printf("[at86rf2xx] EVT - RX_END\n");
			at86rf2xx_receive_data();
		}
	}
}

void at86rf2xx_receive_data() {
	/*  print the length of the frame
	*  (including the header)
	*/

	size_t pkt_len = at86rf2xx.rx_len();
	Serial.printf("Frame length: %d",pkt_len);

	/*  Print the frame */
	uint8_t data[pkt_len];
	at86rf2xx.rx_read(data, pkt_len, 0);
	printf("Frame dump (ASCII): %s", data);

	/* How many frames is this so far?  */
	printf("Total frames received: %d\n",++received);
}

void main()
{

	at86rf2xx.init(SEL_CS, IRQ_GPIO, SLP_TR_GPIO, RESET_PIN);
	at86rf2xx.set_chan(CHANNEL); // set channel

	while(1) 
	{
		if (at86rf2xx.events)
			at86rf2xx_eventHandler();
	}
}


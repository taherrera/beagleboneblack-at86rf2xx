
#include "../../at86rf2xx/at86rf2xx.h"
#include <stdio.h>
int main() {
	//printf("TX power: %d\n", get_txpower()); /* Not working  */
	//printf("PAN: %d\n", get_pan()); /* 0  */
	reg_read(AT86RF2XX_REG__PHY_TX_PWR); /* Segmentation Fault */
	//printf("TX_PWR: %d\n",reg_read(AT86RF2XX_REG__PHY_TX_PWR));
	//printf("Channel: %d\n", get_chan());
	//printf("Long Addr: %d, Short Addr: %d\n", get_addr_long(), get_addr_short());

	return 1;
}

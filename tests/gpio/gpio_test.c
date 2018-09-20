/**
 * @defgroup    test
 * @ingroup     test
 * @brief       test the GPIO drivers for the BBB
 *

 * @{
 * @file
 * @brief       test GPIOs for the BBB
 *
 * @author      Tomás Herrera <taherrera@uc.cl>
 */

#include <stdio.h>
#include <unistd.h>
#include "../../periph/gpio.h"

#define GPIO 66 // pin 7 in P8


int main(void)
{
	if (gpio_init((gpio_t) GPIO, (gpio_mode_t) GPIO_OUT))
	{
		printf("Error: init pin\n");
		return 0;
	}
	gpio_write((gpio_t) GPIO, 0);
	sleep(1);
	gpio_write((gpio_t) GPIO, 1);
	sleep(1);
	gpio_write((gpio_t) GPIO, 0);
	sleep(1);
	gpio_write((gpio_t) GPIO, 1);
	
	return 0;


}

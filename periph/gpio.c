/**
 * @defgroup    drivers_periph_gpio GPIO
 * @ingroup     drivers_periph
 * @brief       Low-level GPIO peripheral driver
 *
 * @{
 * @file
 * @brief       Low-level GPIO peripheral driver interface for the BBB
 *
 * @author      Tomás Herrera <taherrera@uc.cl>
 */


#include "gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static gpio_t defined_pins[100];
static int defined_pins_counter = 0;

int gpio_init(gpio_t pin, gpio_mode_t mode)
{
	bool defined = 0;;

	/* check if pin not in already defined pins */
	int i;
	for (i=0;i<defined_pins_counter;i++)
	{
		if (pin == defined_pins[i])
		{
			defined = 1;
		} 
	}

	/* Increase number of pins defined as gpio */

	FILE *fptr;
	if (!defined)
	{

		++defined_pins_counter;
		fptr = fopen("/sys/class/gpio/export","w");
		if (fptr == NULL)
		{
			printf("Error creating gpio file\n");
			return 1;
		}

		/* Create gpio{$pin} file */
		fprintf(fptr,"%d",pin);
	}

	char gpio_file_path[30];
	sprintf(gpio_file_path,"/sys/class/gpio/gpio%d/direction",pin);

	fptr = fopen(gpio_file_path,"w");
	if (fptr == NULL)
	{
		printf("Error Reading gpio_file_path\n");
		return 1;
	}

	if (mode == (gpio_mode_t) GPIO_IN)	
	{
		fprintf(fptr,"in");
	}else if (mode == (gpio_mode_t) GPIO_OUT)
	{
		fprintf(fptr,"out");
	}else{
		printf("Error: GPIO mode not defined\n");
		fclose(fptr);
		return 1;
	}

	fclose(fptr);
	return 0;
	
}

void gpio_write(gpio_t pin, int value)
{
	bool defined = 0;;
	/* check if pin is defined */
	int i;
	for (i=0;i<defined_pins_counter;i++)
	{
		if (pin == defined_pins[i])
		{
			defined = 1;
		} 
	}

	if (!defined)
	{
		printf("Error: gpio pin mode not defined");
		return;
	}

	char gpio_file_path[30];
	sprintf(gpio_file_path,"/sys/class/gpio/gpio%d/value",pin);

	FILE *fptr;
	fptr = fopen(gpio_file_path,"w");
	if (fptr == NULL)
	{
		printf("Error Reading gpio_file_path");
		return;
	}
	
	fprintf(fptr,"%d",value);
	
}

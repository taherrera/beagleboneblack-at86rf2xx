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
	#ifdef DEBUG
	printf("gpio_init: defined = %d \n", defined);
	printf("gpio_init: defined_pins_counter = %d \n", defined_pins_counter);
	#endif

	/* Increase number of pins defined as gpio */

	FILE *fptr;
	if (!defined)
	{

		defined_pins[defined_pins_counter++] = pin;
		fptr = fopen("/sys/class/gpio/export","w");
		if (fptr == NULL)
		{
			printf("Error creating gpio file\n");
			return 1;
		}

		#ifdef DEBUG
		printf("gpio_init: Creating gpio %d using export fileptr: %s \n",pin, fptr);
		#endif

		/* Create gpio{$pin} file */
		fprintf(fptr,"%d",pin);
		fclose(fptr);
		
	}

	#ifdef DEBUG
	printf("gpio_init: defined_pins_counter = %d \n", defined_pins_counter);
	#endif

	char gpio_file_path[30];
	sprintf(gpio_file_path,"/sys/class/gpio/gpio%d/direction",pin);

	fptr = fopen(gpio_file_path,"w");
	if (fptr == NULL)
	{
		printf("Error Reading gpio_file_path: %s \n",gpio_file_path);
		return 1;
	}


	if (mode == (gpio_mode_t) GPIO_IN)	
	{
		fprintf(fptr,"in");
	}else if (mode == (gpio_mode_t) GPIO_OUT)
	{
		fprintf(fptr,"out");
	}else{
		printf("Error: GPIO mode %d not defined \n", mode);
		fclose(fptr);
		return 1;
	}

	fclose(fptr);
	return 0;
	
}

static bool _check(pin)
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
		printf("Error: gpio pin %d not defined \n",pin);
		printf("Warning: defined_pins_counter = %d", defined_pins_counter);
		for (i=0;i<defined_pins_counter;i++)
			printf("Warning: defined pins are: %d \n",defined_pins[i]);
		return defined;
	}
	return defined;
}

void gpio_write(gpio_t pin, int value)
{
	_check(pin)

	char gpio_file_path[30];
	sprintf(gpio_file_path,"/sys/class/gpio/gpio%d/value",pin);

	FILE *fptr;
	fptr = fopen(gpio_file_path,"w");
	if (fptr == NULL)
	{
		printf("Error: Reading gpio_file_path: %s \n", gpio_file_path);
		return;
	}
	
	#ifdef DEBUG
	printf("gpio_write: Writing %d to file %p \n",value, gpio_file_path);
	#endif
	
	fprintf(fptr,"%d",value);
	fclose(fptr);
}

int gpio_read(gpio_t pin)
{
	if (_check(pin))
		return;

	char gpio_file_path[30];
	sprintf(gpio_file_path,"/sys/class/gpio/gpio%d/value",pin);

	FILE *fptr;
	fptr = fopen(gpio_file_path,"r");
	if (fptr == NULL)
	{
		printf("Error: Reading gpio_file_path: %s \n", gpio_file_path);
		return;
	}
	
	#ifdef DEBUG
	printf("gpio_write: Writing %d to file %p \n",value, gpio_file_path);
	#endif
	
	int c = fgetc(fptr);
	fclose(fptr);
	return c;
}

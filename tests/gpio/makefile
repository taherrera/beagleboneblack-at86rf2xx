
# Compiler
CC = gcc

# Compiler Flags
CCFLAGS = -g -Wall

#path to gpio
GPIO_PATH=../../periph/

#default compilation
default: gpio_test

%.o: $(GPIO_PATH)%.c $(GPIO_PATH)gpio.h
	$(CC) -c -o $@ $< $(CFLAGS)

gpio_test: gpio_test.o gpio.o
	$(CC) $(CFLAGS) -o gpio_test gpio.o gpio_test.o


clean:
	$(RM) gpio_test *.o *~

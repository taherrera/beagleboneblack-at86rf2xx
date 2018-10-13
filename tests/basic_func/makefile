
# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I.

#path to gpio
GPIO_PATH=../../periph/


%.o: $(GPIO_PATH)%.c $(GPIO_PATH)spi.o
	$(CC) -c -o $@ $< $(CFLAGS)

at_setup: at_setup.o spi.o
	$(CC) -o at_setup at_setup.o spi.o

default: at_setup

clean:
	rm *.o

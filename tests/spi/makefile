
# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I.

#path to gpio
GPIO_PATH=../../periph/


%.o: $(GPIO_PATH)%.c $(GPIO_PATH)spi.o
	$(CC) -c -o $@ $< $(CFLAGS)

spi_test: spi_test.o spi.o
	$(CC) -o spi_test spi_test.o spi.o

default: spi_test



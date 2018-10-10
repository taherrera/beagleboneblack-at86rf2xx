
# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I.

#path to gpio
GPIO_PATH=../../periph/


%.o: $(GPIO_PATH)%.c $(GPIO_PATH)spi.o
	$(CC) -c -o $@ $< $(CFLAGS)

com_test: com_test.o spi.o
	$(CC) -o com_test com_test.o spi.o

default: com_test



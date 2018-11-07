
# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I.

#path to gpio
GPIO_PATH=../../periph/


%.o: $(GPIO_PATH)%.c $(GPIO_PATH)spi.o
	$(CC) -c -o $@ $< $(CFLAGS)

com_read: com_read.o spi.o
	$(CC) -o com_read com_read.o spi.o

default: com_read

com_write: com_write.o spi.o
	$(CC) -o com_write com_write.o spi.o

clean:
	rm *.o


# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I.

OBJ = radiosend.o spi.o gpio.o \
	at86rf2xx.o at86rf2xx-getset.o \
	at86rf2xx-internal.o 

ODIR=obj/

#path to gpio
GPIO_PATH=../../periph/
SPI_PATH=../../periph/
RADIO_PATH=../../at86rf2xx/

RADIO_DEPS = at86rf2xx-getset.o at86rf2xx-internal.o
RADIO_OBJS = $(ODIR)at86rf2xx-getset.o $(ODIR)at86rf2xx-internal.o



at86rf2xx-getset.o: $(RADIO_PATH)at86rf2xx-getset.c
	$(CC) -c -o $(ODIR)at86rf2xx-getset.o $(RADIO_PATH)at86rf2xx-getset.c $(CFLAGS)

at86rf2xx-internal.o: $(RADIO_PATH)at86rf2xx-internal.c
	$(CC) -c -o $(ODIR)at86rf2xx-internal.o $(RADIO_PATH)at86rf2xx-internal.c $(CFLAGS)

gpio.o: $(GPIO_PATH)gpio.c
	$(CC) -c -o $(ODIR)gpio.o $(GPIO_PATH)gpio.c $(CFLAGS)

spi.o: $(SPI_PATH)spi.c
	$(CC) -c -o $(ODIR)spi.o $(SPI_PATH)spi.c $(CFLAGS)

at86rf2xx.o: $(RADIO_PATH)at86rf2xx.c $(RADIO_DEPS)
	$(CC) -c -o $(ODIR)at86rf2xx.o $(RADIO_PATH)at86rf2xx.c $(RADIO_OBJS) $(CFLAGS)

radiosend.o: radiosend.c at86rf2xx.o 
	$(CC) -c -o $(ODIR)radiosend.o radiosend.c $(ODIR)at86rf2xx.o $(CFLAGS)   

send: $(OBJ)
	$(CC) -o send $(ODIR)radiosend.o $(CFLAGS)

default: send

clean:
	rm send $(OBJ)

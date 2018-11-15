
# Compiler
CC=gcc

# Compiler Flags
CFLAGS=-I. -Wall -DATDEBUG

OBJ = radiosend.o radiorecv.o spi.o gpio.o \
	at86rf2xx.o at86rf2xx-getset.o \
	at86rf2xx-internal.o 

ODIR=obj/

#path to gpio
GPIO_PATH=../../periph
SPI_PATH=../../periph
RADIO_PATH=../../at86rf2xx


# search path of target if file not in current path (.)
VPATH = $(GPIO_PATH):$(SPI_PATH):$(RADIO_PATH)

RADIO_FILES= $(RADIO_PATH)/at86rf2xx-getset.c $(RADIO_PATH)/at86rf2xx-internal.c
RADIO_DEPS = at86rf2xx-getset.o at86rf2xx-internal.o
RADIO_OBJS = $(ODIR)at86rf2xx-getset.o $(ODIR)at86rf2xx-internal.o

.DEFAULT = default

default: send

at86rf2xx-getset.o: at86rf2xx-getset.c
	$(CC) -c -o $(ODIR)$@ $^ $(CFLAGS)

at86rf2xx-internal.o: at86rf2xx-internal.c
	$(CC) -c -o $(ODIR)$@ $^ $(CFLAGS)

gpio.o: gpio.c
	$(CC) -c -o $(ODIR)$@ $^ $(CFLAGS)

spi.o: spi.c
	$(CC) -c -o $(ODIR)$@ $^ $(CFLAGS)

# $< first requisite of for this target

at86rf2xx.o: at86rf2xx.c $(RADIO_DEPS)
	$(CC) -c -o $(ODIR)$@ $< $(CFLAGS)

# $@ = target
radiosend.o: radiosend.c at86rf2xx.o 
	$(CC) -c -o $(ODIR)$@ $< $(CFLAGS)   

radiorecv.o: radiorecv.c at86rf2xx.o
	$(CC) -c -o $(ODIR)$@ $< $(CFLAGS)

send: $(OBJ)
	$(CC) -o $@ $(ODIR)radiosend.o $(ODIR)at86rf2xx.o $(RADIO_OBJS) $(ODIR)spi.o $(ODIR)gpio.o $(CFLAGS)

recv: $(OBJ)
	$(CC) -o $@ $(ODIR)radiorecv.o $(ODIR)at86rf2xx.o $(RADIO_OBJS) $(ODIR)spi.o $(ODIR)gpio.o $(CFLAGS)

$(OBJ): | mkdir

# .PHONY mkdir not an actual file
# -mkdir prevent errors stopping make
.PHONY : mkdir
mkdir:
	-mkdir $(ODIR)


.PHONY : clean
clean:
	-rm send
	-rm -r $(ODIR)

# $^ lists all prerequisites of the rule (where they where found)

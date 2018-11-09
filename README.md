# beaglebone-at86rf233
Simple BeagleBoneBlack driver for the AT86RF233 IEEE802.15.4 radio module

This is a C port of the AT86RF233 driver from [RIOT-OS](https://github.com/RIOT-OS/RIOT) and [arduino-at86rf233](https://github.com/msolters/arduino-at86rf233/blob/master/arduino-at86rf233.ino)

## Radio Hardware
This software is designed to be used with ATMEL's AT86RF233 IEEE802.15.4 radio, [available as a $30USB radio extension board (REB)](http://www.mouser.com/ProductDetail/Atmel/ATREB233-XPRO/?qs=HVbQlW5zcXX%2FEgqNxRIBfA%3D%3D).

![](http://media.digikey.com/Photos/Atmel%20Photos/ATREB233-XPRO.JPG)

## Connect the AT86RF233 to the BeagleBoneBlack
In this example, we will be using a BeagleBoneBlack. 


Here's the wiring setup.

BBB            Extension Board  | (AT86RF2xx)

GPIO\_60 (12)   --- 7 PWM(+)    | (8 RSTN) 

SPIO\_CSO (17)  --- 15 SPI_SS_A | (23 SEL)

SPIO\_D1 (18)   --- 16 SPI_MOSI | (22 MOSI)

SPIO\_DO (21)   --- 17 SPI_MISO | (20 MISO)

SPIO\_SLCK (22) --- 18 SPI_SCK  | (19 SCLK)

GND             --- 10          | (11 SLP_TR)

TODO (__experimental__):

GPIO\_48 (15)   --- 9 IRQ/GPIO  | (24 IRQ)

GPIO\_49 (23)   --- 10          | (11 SLP_TR)

Pinout of the BBB can be found in lect/beaglebone-black-pinout.jpg

## Instalation

**You must run periph/scripts/install.sh as superuser**. This will enable access to the SPI pins on the BBB via userspace. Note that it also adds a bootstrap script to your crontab to enable a spi device on /dev/spi*:

```
sudo su
chmod a+x periph/scripts/install.sh
./periph/scripts/install.sh
```

## Testing

What could fail is SPI setup due to OS updates. To test run tests/coms/com_read

If SPI is working the output should be:

```
Should be b (reset value), outputing: **b**
```

If not:
```
Should be b (reset value), outputing: **0**
```



## Driver Configuration

Without further configuration, this library will use the default AT86RF2xx parameters contained in `at86rf2xx-defaults.h`.  Most radio parameters can be updated manually by using the set/getters enumerated in `at86rf2xx-getset.c`.  For example, to change the radio channel to `25`, simply call `set_chan(25)` on the at86rf2xx device after initialization:

```c
	at86rf2xx.init(SEL_CS, IRQ_GPIO, SLP_TR_GPIO, RESET_PIN);
	at86rf2xx.set_chan(CHANNEL); // set channel
```

### Important notes:

**SEL_CS is not configurable**. You must use pin 17 on the BBB.

# arduino-at86rf233
Simple Arduino driver for the AT86RF233 802.15.4 radio module

This is a C++ port of the AT86RF233 driver from [RIOT-OS](https://github.com/RIOT-OS/RIOT) and [arduino-at86rf233.ino](https://github.com/msolters/arduino-at86rf233/blob/master/arduino-at86rf233.ino)

## Radio Hardware
Designed to be used with ATMEL's AT86RF233 802.15.4 radio, [available as a $30USB radio extension board (REB)](http://www.mouser.com/ProductDetail/Atmel/ATREB233-XPRO/?qs=HVbQlW5zcXX%2FEgqNxRIBfA%3D%3D).

![](http://media.digikey.com/Photos/Atmel%20Photos/ATREB233-XPRO.JPG)

## Connect the AT86RF233 to the BeagleBoneBlack
In this example, we will be using a BeagleBoneBlack. 


Here's the wiring setup.

BBB          Extension Board  | (AT86RF2xx)

GPIO_60 (12)   --- 7 PWM(+)    | (8 RSTN) 
GPIO_48 (15)   --- 9 IRQ/GPIO  | (24 IRQ)
GPIO_49 (23)   --- 10          | (11 SLP_TR)
SPIO_CSO (17)  --- 23 SPI_SS_A | (23 SEL)
SPIO_D1 (18)   --- 16 SPI_MOSI | (22 MOSI)
SPIO_DO (21)   --- 17 SPI_MISO | (20 MISO)
SPIO_SLCK (22) --- 18 SPI_SCK  | (19 SCLK)


## Driver Configuration
Without further configuration, this library will use the default AT86RF2xx parameters contained in `at86rf2xx-defaults.h`.  Most radio parameters can be updated manually by using the set/getters enumerated in `at86rf2xx-getset.c`.  For example, to change the radio channel to `25`, simply call `set_chan(25)` on the at86rf2xx device after initialization:

```cpp
	at86rf2xx.init(SEL_CS, IRQ_GPIO, SLP_TR_GPIO, RESET_PIN);
	at86rf2xx.set_chan(CHANNEL); // set channel
```
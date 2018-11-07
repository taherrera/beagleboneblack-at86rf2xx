/*
 * Copyright (C) 2013 Alaeddine Weslati <alaeddine.weslati@inria.fr>
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_at86rf2xx
 * @{
 *
 * @file
 * @brief       Implementation of driver internal functions
 *
 * @author      Alaeddine Weslati <alaeddine.weslati@inria.fr>
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 * @author      Joakim Nohlgård <joakim.nohlgard@eistec.se>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Mark Solters <msolters@gmail.com>
 * @author      Tomás Herrera <taherrera@uc.cl> 
 *
 * @}
 */

#include "../periph/spi.h"
#include "../periph/gpio.h"

#include "at86rf2xx.h"

void reg_write(const uint8_t addr, const uint8_t value)
{
    uint8_t writeCommand = addr | AT86RF2XX_ACCESS_REG | AT86RF2XX_ACCESS_WRITE;
    //gpio_write(cs_pin, 0);
    uint8_t inbuff[2];
    uint8_t outbuff[2] = {writeCommand, value};
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
    //gpio_write(cs_pin, 1);
}

uint8_t reg_read(const uint8_t addr)
{
    uint8_t inbuff[2];
    uint8_t readCommand = addr | AT86RF2XX_ACCESS_REG | AT86RF2XX_ACCESS_READ;
    uint8_t outbuff[2] = {readCommand, 0x00};
    //gpio_write(cs_pin, 0);
    printf("Transfering bytes\n");
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
    //gpio_write(cs_pin, 1);
    printf("Bytes transfered\n");
    return (uint8_t) inbuff[0];
}

void sram_read(const uint8_t offset, uint8_t *inbuff, const size_t len)
{

    uint8_t readCommand = AT86RF2XX_ACCESS_SRAM | AT86RF2XX_ACCESS_READ;
    //gpio_write(cs_pin, 0);
    uint8_t outbuff[256] = {readCommand,offset};
    //spi_transfer_byte(readCommand);
    //spi_transfer_byte((uint8_t) offset);
    int b;
    for (b=0; b<len; b++) {
        outbuff[b+2] = 0x00;
    }
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, len+2);
    //gpio_write(cs_pin, 0);
}

void sram_write(const uint8_t offset, const uint8_t *data, const size_t len)
{
    uint8_t writeCommand = AT86RF2XX_ACCESS_SRAM | AT86RF2XX_ACCESS_WRITE;
    uint8_t outbuff[256] = {writeCommand,offset};
    //gpio_write(cs_pin, 0);
    int b;
    for (b=0; b<len; b++) {
        outbuff[b+2] = data[b];
    }
    uint8_t inbuff[2048];
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, len+2);
    //gpio_write(cs_pin, 1);
}

void fb_read(uint8_t *inbuff, const size_t len)
{
    uint8_t readCommand = AT86RF2XX_ACCESS_FB | AT86RF2XX_ACCESS_READ;
    //gpio_write(cs_pin, 0);
    char outbuff[256] = {readCommand};
    int b;
    for (b=0; b<len; b++) {
      outbuff[b+1] = 0x00;
    }
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, len+1);
    //gpio_write(cs_pin, 1);
}

uint8_t get_status(void)
{
    /* if sleeping immediately return state */
    if(state == AT86RF2XX_STATE_SLEEP)
        return state;
    printf("Reading Register to get state\n");
    return reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
}

void assert_awake(void)
{
    printf("Asserting Awake\n");
    if(get_status() == AT86RF2XX_STATE_SLEEP) {
	printf("Device was Sleep");
        /* wake up and wait for transition to TRX_OFF */
        gpio_write(sleep_pin, 0);
        usleep(AT86RF2XX_WAKEUP_DELAY);

        /* update state */
	printf("Updating State");
        state = reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
    }else{
	printf("Device was Awake");
    }
}

void hardware_reset(void)
{
    /* wake up from sleep in case radio is sleeping */
    assert_awake();

    /* trigger hardware reset */

    gpio_write(reset_pin, 0);
    usleep(AT86RF2XX_RESET_PULSE_WIDTH);
    gpio_write(reset_pin, 1);
    usleep(AT86RF2XX_RESET_DELAY);
}

void force_trx_off(void)
{
    reg_write(AT86RF2XX_REG__TRX_STATE, AT86RF2XX_TRX_STATE__FORCE_TRX_OFF);
    while (get_status() != AT86RF2XX_STATE_TRX_OFF);
}

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
#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include "at86rf2xx.h"

uint8_t addr_short[2];              /**< the radio's short address */
uint8_t addr_long[8];               /**< the radio's long address */
uint16_t options;                   /**< state of used options */
uint8_t idle_state;                 /**< state to return to after sending */

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
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] Transfering bytes\n");
    #endif 
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, 2);
    //gpio_write(cs_pin, 1);
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] Bytes transfered\n");
    #endif
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
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] fb_read called\n");
    #endif

    uint8_t readCommand = AT86RF2XX_ACCESS_FB | AT86RF2XX_ACCESS_READ;
    //gpio_write(cs_pin, 0);
    char outbuff[256] = {readCommand};
    int b;
    for (b=0; b<len; b++) {
      outbuff[b+1] = 0x00;
    }
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] fb_read now calling transfer bytes\n");
    #endif
    spi_transfer_bytes(SPI_BUS, SPI_CS, CONT, (void*) outbuff, (void*) inbuff, len+1); // was len+1
    //gpio_write(cs_pin, 1);
}

uint8_t get_status(void)
{
    /* if sleeping immediately return state */
    if(state == AT86RF2XX_STATE_SLEEP)
        return state;
    #ifdef DEBUG
    printf("[at86rf2xx-internal.c] Reading Register to get state\n");
    #endif
    return reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
}

void assert_awake(void)
{
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] Asserting Awake\n");
    #endif
    if(get_status() == AT86RF2XX_STATE_SLEEP) {
	printf("[at86rf2xx-internal.c] Device was Asleep\n");
        /* wake up and wait for transition to TRX_OFF */
        //gpio_write(sleep_pin, 0);
        usleep(AT86RF2XX_WAKEUP_DELAY);

        /* update state */
	printf("[at86rf2xx-internal.c] Updating State\n");
        state = reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
    }else{
	printf("[at86rf2xx-internal.c] Device was Awake\n");
    }
}

void hardware_reset(void)
{
    /* wake up from sleep in case radio is sleeping */
    assert_awake();

    /* trigger hardware reset */
    #ifdef ATDEBUG
    printf("[at86rf2xx-internal.c] hardware_reset: reset_pin = %d\n", reset_pin);
    #endif 

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

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

#include "periph/spi.h"
#include "periph/gpio.h"

#include "at86rf2xx.h"

void AT86RF2XX::reg_write(const uint8_t addr,
                         const uint8_t value)
{
    uint8_t writeCommand = addr | AT86RF2XX_ACCESS_REG | AT86RF2XX_ACCESS_WRITE;
    gpio_write(cs_pin, 0);
    spi_transfer_byte(writeCommand);
    spi_transfer_byte(value);
    gpio_write(cs_pin, 1);
}

uint8_t AT86RF2XX::reg_read(const uint8_t addr)
{
    uint8_t value;
    uint8_t readCommand = addr | AT86RF2XX_ACCESS_REG | AT86RF2XX_ACCESS_READ;
    gpio_wirte(cs_pin, 0);
    spi_transfer_byte(readCommand);
    value = spi_transfer_byte(0x00);
    gpio_write(cs_pin, 1);

    return (uint8_t) value;
}

void AT86RF2XX::sram_read(const uint8_t offset,
                         uint8_t *data,
                         const size_t len)
{
    uint8_t readCommand = AT86RF2XX_ACCESS_SRAM | AT86RF2XX_ACCESS_READ;
    gpio_write(cs_pin, 0);
    spi_transfer_byte(readCommand);
    spi_transfer_byte((uint8_t) offset);
	int b;
    for (b=0; b<len; b++) {
      data[b] = spi_transfer_byte(0x00);
    }
    gpio_write(cs_pin, 0);
}

void AT86RF2XX::sram_write(const uint8_t offset,
                          const uint8_t *data,
                          const size_t len)
{
    uint8_t writeCommand = AT86RF2XX_ACCESS_SRAM | AT86RF2XX_ACCESS_WRITE;
    gpio_write(cs_pin, 0);
    spi_transfer_byte(writeCommand);
    spi_transfer_byte((char)offset);
    for (int b=0; b<len; b++) {
      spi_transfer_byte(data[b]);
    }
    gpio_write(cs_pin, 1);
}

void AT86RF2XX::fb_read(uint8_t *data,
                       const size_t len)
{
    byte readCommand = AT86RF2XX_ACCESS_FB | AT86RF2XX_ACCESS_READ;
    gpio_write(cs_pin, 0);
    spi_transfer_byte(readCommand);
    for (int b=0; b<len; b++) {
      data[b] = spi_transfer_byte(0x00);
    }
    gpio_write(cs_pin, 1);
}

uint8_t AT86RF2XX::get_status()
{
    /* if sleeping immediately return state */
    if(state == AT86RF2XX_STATE_SLEEP)
        return state;

    return reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
}

void AT86RF2XX::assert_awake()
{
    if(get_status() == AT86RF2XX_STATE_SLEEP) {
        /* wake up and wait for transition to TRX_OFF */
        gpio_write(sleep_pin, 0);
        delay(AT86RF2XX_WAKEUP_DELAY);

        /* update state */
        state = reg_read(AT86RF2XX_REG__TRX_STATUS) & AT86RF2XX_TRX_STATUS_MASK__TRX_STATUS;
    }
}

void AT86RF2XX::hardware_reset()
{
    /* wake up from sleep in case radio is sleeping */
    //delay(50); // Arduino seems to hang without some minimum pause here
    assert_awake();

    /* trigger hardware reset */

    gpio_write(reset_pin, 0);
    delay(AT86RF2XX_RESET_PULSE_WIDTH);
    gpio_write(reset_pin, 1);
    delay(AT86RF2XX_RESET_DELAY);
}

void AT86RF2XX::force_trx_off()
{
    reg_write(AT86RF2XX_REG__TRX_STATE, AT86RF2XX_TRX_STATE__FORCE_TRX_OFF);
    while (get_status() != AT86RF2XX_STATE_TRX_OFF);
}

/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @brief       Debian family specific code
 * @{
 *
 * @file
 * @brief           Debian specific definitions for internal peripheral handling
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef PERIPH_CPU_H
#define PERIPH_CPU_H



#define HAVE_SPI_CLK_T
typedef enum {
    SPI_CLK_100KHZ = 100000,    /**< 100KHz */
    SPI_CLK_400KHZ = 400000,    /**< 400KHz */
    SPI_CLK_1MHZ   = 1000000,   /**< 1MHz */
    SPI_CLK_5MHZ   = 5000000,   /**< 5MHz */
    SPI_CLK_10MHZ  = 10000000,         /**< not supported */
} spi_clk_t;
/** @} */
#endif /* ndef DOXYGEN */



#endif // PERIPH_CPU_H

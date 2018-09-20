/**
 * @defgroup    spi drivers for the BBB
 * @ingroup     drivers_netdev
 *
 * This interface bridges 
 *
 * @{
 *
 * @file
 * @brief       Interface definition for AT86RF2xx based drivers
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Daniel Krebs <github@daniel-krebs.net>
 * @author      Mark Solters <msolters@gmail.com>
 * @author		Tomás Herrera <taherrera@uc.cl>
 */

#ifndef PERIPH_SPI_H
#define PERIPH_SPI_H

/**
 * @brief   Default type for SPI devices
 */

typedef unsigned int spi_t;


/**
 * @brief   Chip select pin type overlaps with gpio_t so it can be casted to
 *          this
 */

typedef gpio_t spi_cs_t;


/**
 * @brief   Status codes used by the SPI driver interface
 */
enum {
    SPI_OK          =  0,   /**< everything went as planned */
    SPI_NODEV       = -1,   /**< invalid SPI bus specified */
    SPI_NOCS        = -2,   /**< invalid chip select line specified */
    SPI_NOMODE      = -3,   /**< selected mode is not supported */
    SPI_NOCLK       = -4    /**< selected clock value is not supported */
};


/**
 * @brief   Available SPI modes, defining the configuration of clock polarity
 *          and clock phase
 *
 * RIOT is using the mode numbers as commonly defined by most vendors
 * (https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers):
 *
 * - MODE_0: CPOL=0, CPHA=0 - The first data bit is sampled by the receiver on
 *           the first SCK rising SCK edge (this mode is used most often).
 * - MODE_1: CPOL=0, CPHA=1 - The first data bit is sampled by the receiver on
 *           the second rising SCK edge.
 * - MODE_2: CPOL=1, CPHA=0 - The first data bit is sampled by the receiver on
 *           the first falling SCK edge.
 * - MODE_3: CPOL=1, CPHA=1 - The first data bit is sampled by the receiver on
 *           the second falling SCK edge.
 */

typedef enum {
    SPI_MODE_0 = 0,         /**< CPOL=0, CPHA=0 */
    SPI_MODE_1,             /**< CPOL=0, CPHA=1 */
    SPI_MODE_2,             /**< CPOL=1, CPHA=0 */
    SPI_MODE_3              /**< CPOL=1, CPHA=1 */
} spi_mode_t;


/**
 * @brief   Available SPI clock speeds
 *
 * The actual speed of the bus can vary to some extend, as the combination of
 * CPU clock and available prescaler values on certain platforms may not make
 * the exact values possible.
 */

typedef enum {
    SPI_CLK_100KHZ = 0,     /**< drive the SPI bus with 100KHz */
    SPI_CLK_400KHZ,         /**< drive the SPI bus with 400KHz */
    SPI_CLK_1MHZ,           /**< drive the SPI bus with 1MHz */
    SPI_CLK_5MHZ,           /**< drive the SPI bus with 5MHz */
    SPI_CLK_10MHZ           /**< drive the SPI bus with 10MHz */
} spi_clk_t;


/**
 * @brief   Basic initialization of the given SPI bus
 *
 * This function does the basic initialization including pin configuration for
 * MISO, MOSI, and CLK pins. After initialization, the given device should be
 * in power down state.
 *
 * This function is intended to be called by the board initialization code
 * during system startup to prepare the (shared) SPI device for further usage.
 * It uses the board specific initialization parameters as defined in the
 * board's `periph_conf.h`.
 *
 * Errors (e.g. invalid @p bus parameter) are not signaled through a return
 * value, but should be signaled using the assert() function internally.
 *
 * @note    This function MUST not be called more than once per bus!
 *
 * @param[in] bus       SPI device to initialize
 */
void spi_init(spi_t bus);


/**
 * @brief Transfer one byte on the given SPI bus
 *
 * @param[in] bus       SPI device to use
 * @param[in] cs        chip select pin/line to use, set to SPI_CS_UNDEF if chip
 *                      select should not be handled by the SPI driver
 * @param[in] cont      if true, keep device selected after transfer
 * @param[in] out       byte to send out, set NULL if only receiving
 *
 * @return              the received byte
 */
uint8_t spi_transfer_byte(spi_t bus, spi_cs_t cs, bool cont, uint8_t out);

#endif /* PERIPH_SPI_H */
/** @} */

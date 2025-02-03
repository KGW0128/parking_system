#include "common/def.h"

/*
 * Set to 1, spi api will work in master mode
 * else in slave mode
 */
#define SPI_CONFIG_AS_MASTER 1

/*
 * Config SPI pin diagram
 */
#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_PIN PINB
#define SPI_MOSI PORTB2
#define SPI_MISO PORTB3
#define SPI_SS PORTB0
#define SPI_SCK PORTB1

void spi_init();
uint8_t spi_transmit(uint8_t data);

#define ENABLE_CHIP() (SPI_PORT &= (~(1 << SPI_SS)))
#define DISABLE_CHIP() (SPI_PORT |= (1 << SPI_SS))
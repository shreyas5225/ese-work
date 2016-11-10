#include "MKL25Z4.h"

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#define TEST_LOW GPIOC_PCOR |= GPIO_PCOR_PTCO(0x10) //Assigned debug pin
#define TEST_HIGH GPIOC_PSOR |= GPIO_PSOR_PTSO(0x10) //Assigned debug pin
#define SPI_WAIT_RX_DATA while (!(SPI0_S & SPI_S_SPRF_MASK))  //Waits for the receive data ready
#define SPI_WAIT_TX_DATA while (!(SPI0_S & SPI_S_SPTEF_MASK)) //Waits for the transmit data ready
#define SPI_RD_WR_REG SPI0_D  //Read/Write register
void spi_init();
unsigned char  spi_write(char data);
unsigned char spi_read();
void spi_flush();
void spi_init( void);
void spi_test( void);

#endif /* SOURCES_SPI_H_ */

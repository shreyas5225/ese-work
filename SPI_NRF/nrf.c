#include "spi.h"
#include "nrf.h"
#include "nRF24L01.h"


void nrf_configure(void)
{
	spi_init();	//Initializes SPI
}

void nrf_writeregister(unsigned char address) //write command to SPI
{
	spi_write(0x20|address);
}

void nrf_readregister(unsigned char address) //read command to SPI
{
	spi_write(0x00|address);
}

void nrf_flush_fifo_transmit() //Flush the nrf transmit buffer
{
	TEST_LOW;
	spi_write(0xE1);
	TEST_HIGH;
}

void nrf_flush_fifo_receive() //Flush the nrf receive buffer
{
	TEST_LOW;
	spi_write(0xE2);
	TEST_HIGH;
}

void nrf_transmitdata() //Transmit data to nrf buffer
{
	TEST_LOW;
	spi_write(W_TXPAYLOAD);
	spi_write(0x10);
	TEST_HIGH;
}

void nrfreaddata() //Receive data from nrf buffer
{
	char c;
	TEST_LOW;
	spi_read(R_RXPAYLOAD);
	spi_write(0xff);
	c=spi_read();
	TEST_HIGH;

	nrf_read_fifostatus();
}

void nrf_statusread() //Read the status register
{
	char c;
	TEST_LOW;
	nrf_readregister(NORDIC_STATUS_REG);
	spi_write(0xFF);
	c=spi_read();
	TEST_HIGH;
}

void nrf_rf_setup_transmit() //Setup the RF register
{
	TEST_LOW;
	nrf_writeregister(NORDIC_RF_SETUP_REG);
	spi_write(0x84);
	TEST_HIGH;
}

void nrf_rf_setup_receive() //Read the RF register
{
	char c;
	TEST_LOW;
	nrf_writeregister(NORDIC_RF_SETUP_REG);
	spi_write(0xff);
	 c=spi_read();
	TEST_HIGH;

}

void nrf_read_fifostatus() //Read the FIFO register
{
	char c;
	TEST_LOW;
	nrf_readregister(FIFO_STATUS_REG );
	spi_write(0xff);
	 c=spi_read();
	 TEST_HIGH;
}

void nrf_addr_read_rx() //Read the RX address register
{
	int i;
	char c;
	TEST_LOW;
	nrf_readregister(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_write(0xff);
		 c=spi_read();
	 }
	TEST_HIGH;
}

void nrf_addr_write_rx() //Write the RX address register
{
	int i;
	TEST_LOW;
	nrf_writeregister(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_write(0xE7);
	 }
	 TEST_HIGH;
}

void nrf_configure_write() //Write to the configure register
{
	TEST_LOW; //Toggle CS pin
	nrf_writeregister(NORDIC_CONFIG_REG);
	spi_write(0x03);
	TEST_HIGH;  //Toggle CS pin
}

void nrf_configure_read() //Read from the configure register
{
	char c;
	TEST_LOW;
	nrf_readregister(NORDIC_CONFIG_REG);
    c =spi_write(0XFF);
	TEST_HIGH;
}

void nrf_read_pipesize()  //read the data pipe size
{
	int i;
	char c;
	TEST_LOW;
	nrf_readregister(NRF_PIPESIZE);

	 spi_write(0xff);
	 c=spi_read();

	 TEST_HIGH;
}

void nrf_set_pipesize() //set the data pipe size
{
	int i;
	TEST_LOW;
	nrf_writeregister(NRF_PIPESIZE);

	spi_write(0x01);

	TEST_HIGH;
}

void nrf_addr_write_tx() //Write the TX address register
{
	int i;
	TEST_LOW;
	nrf_writeregister(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_write(0xBB);
	 }
	 TEST_HIGH;
}

void nrf_addr_read_tx() //Read the TX address register
{
	int i;
	char c;
	TEST_LOW;
	nrf_readregister(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_write(0xff);
		 c=spi_read();
	 }
	TEST_HIGH;
}

void nrf_read_rxaddr_reg() //read from the datapipe register
{
	int i;
	char c;
	TEST_LOW;
	nrf_readregister(NRF_ENRXADDR);

	 spi_write(0xff);
	 c=spi_read();

	 TEST_HIGH;
}

void  nrf_write_rxaddr_reg() //write to the datapipe register
{
	int i;
	TEST_LOW;
	nrf_writeregister(NRF_ENRXADDR);

	spi_write(0x01);

	 TEST_HIGH;
}

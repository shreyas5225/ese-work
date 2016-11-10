#include <MKL25Z4.h>
#include "spi.h"
#include "nrf.h"
#include "nRF24L01.h"

int main(void)
{
    uint8_t character_array[4] ={0,0,0,0};
    nrf_configure(); //this APi initializes SPI

    nrf_configure_write(); //Write configure to set in receive mode
    nrf_configure_read(); //Read the values to verify if they are correct
    nrf_write_rxaddr_reg(); //Write to the En_rxaddr register to activate data pipe 0
    nrf_read_rxaddr_reg(); //Read the values to verify if they are correct
    nrf_set_pipesize(); //Set the pipe size
    nrf_read_pipesize(); //Read the values to verify if they are valid
    nrf_addr_write_rx(); //Write and set the receive address
    nrf_addr_read_rx(); //Read the values to verify if they are valid

     return 0;	//return type
}

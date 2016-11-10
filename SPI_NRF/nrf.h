#ifndef SOURCES_NRF_H_
#define SOURCES_NRF_H_

#define R_RXPAYLOAD (0x61)
#define NORDIC_CONFIG_REG (0x00)
#define NRF_ENRXADDR (0x02)
#define NORDIC_TXADDR_REG (0x10)
#define FIFO_STATUS_REG (0x17)
#define RX_ADDR_P0_REG (0x0A)
#define NORDIC_POWER_UP (0x01)
#define NORDIC_RF_SETUP_REG (0x06)
#define NORDIC_EN_RXADDR_REG (0x02)
#define NORDIC_POWER_UP_MASK (0x02)
#define NORDIC_POWER_DOWN_MASK (0x00)
#define NORDIC_SETUP_RETR_REG (0x04)
#define NORDIC_EN_AA_REG (0x01)
#define W_TXPAYLOAD (0xA0)
#define NORDIC_STATUS_REG (0x07)
#define NRF_PIPESIZE (0X11)
#define NORDIC_RF_CH_REG (0x05)
#define NORDIC_SETUP_AW_REG (0x03)
#define TX_ADDR (0x10)


void nrf_configure(void);
void nrf_read_fifostatus();
void nrf_read_rxaddr_reg();
void nrf_write_rxaddr_reg();
void nrf_statusread();
void nrf_set_pipesize();
void nrf_read_pipesize();
void nrf_addr_read_rx();
void nrf_addr_write_rx();
void nrf_configure_write();
void nrf_configure_read();
void nrf_readdata();
void nrf_transmitdata();
void nrf_addr_read_tx();
void nrf_addr_write_tx();
void nrf_readregister(unsigned char address);
void nrf_writeregister(unsigned char address);
void nrf_flush_fifo_receive();
void nrf_flush_fifo_transmit();
void nrf_rf_setup_transmit();
void nrf_rf_setup_receive();

#endif /* SOURCES_NRF_H_ */

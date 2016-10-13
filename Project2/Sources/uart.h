/*
 * uart.h
 *
 *  Created on: Oct 8, 2016
 *      Author: shva9978
 */



#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void send_string(char s[]);

void send_char(char c);
void UART0_init();
void uart_init(uint32_t baud);
void UART0_IRQHandler();
void put_data_with_Interrupt(uint8_t *c);
void delayMs(int n);

#endif /* SOURCES_UART_H_ */


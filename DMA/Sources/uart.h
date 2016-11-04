/*
 * uart.h
 *
 *  Created on: 03-Nov-2016
 *      Author: Shreyas
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_
#define MAX_SIZE 8

struct FRDM_Command_t{
	Cmds command;
	uint8_t length;
	uint8_t data[MAX_DATA_SIZE];
	uint16_t checksum;
} FRDM_Cmd;

typedef enum Status{
	ERROR,
	SUCCESS,
};

typedef enum Cmds_t{
	LED_CONFIG
} Cmds ;

typedef enum Colors_t{
	LED_RED,
	LED_BLUE,
	LED_GREEN
} Colors;

void UART_init();
void


#endif /* SOURCES_UART_H_ */

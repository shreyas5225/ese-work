/*
 * uart.h
 *
 *  Created on: 03-Nov-2016
 *      Author: Shreyas
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_
//#define MAX_DATA_SIZE 8

typedef enum Cmds_t{
	LED_CONFIG
} Cmds;

typedef enum Colors_t{
	LED_RED,
	LED_BLUE,
	LED_GREEN
} Colors;

typedef struct FRDM_Command_t{
	Cmds command;
	uint8_t length;
	Colors data;
	uint16_t checksum;
} FRDM_Cmd;

typedef enum Status_t{
	ERROR,
	SUCCESS
}Status;




void UART_init();

void Decode_CI_Msg(FRDM_Cmd *msg);

void Initialize_LED();



#endif /* SOURCES_UART_H_ */

/*
 * uart.c
 *
 *  Created on: 03-Nov-2016
 *      Author: Shreyas
 */
#include "MKL25Z4.h"
#include<stdio.h>
#include <math.h>
#include <string.h>
#include "uart.h"

volatile int count=0;
int Glow = 500;
FRDM_Cmd *msg;

int flag=0;
uint8_t array[10];

void UART0_init(void)
{

	__disable_irq();
	    SIM->SCGC5 |= 0x0200;
		SIM->SCGC4 |= 0x0400;
		SIM->SOPT2 |= 0x04000000;

		PORTA->PCR[2]= 0x0200;
		PORTA->PCR[1]= 0x0200;

		UART0->C2 = 0x00;
		UART0->C1 = 0x00;
		UART0->BDH = 0x00;
		UART0->BDL = 0x17;
		UART0->C4 = 0x0F;

		UART0->C2 = 0x88|0x24;

	__enable_irq();
		NVIC_EnableIRQ(UART0_IRQn);

}

void structure_init (FRDM_Cmd *msg)
{
	msg->command= array[0];
	msg->length= array[1];
	msg->data[0]= array[2];
	msg->checksum= array[3];
	Decode_CI_Msg(msg);
	counter= 0;
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;

}


void Set_red_LED()
{
	 	    TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    TPM2_BASE_PTR->CONTROLS[0].CnV = Glow;
}


void Set_blue_LED()
{

			TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
			TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			TPM0_BASE_PTR->CONTROLS[1].CnV = Glow;

}

void Set_green_LED()
{
				TPM2_BASE_PTR->CONTROLS[1].CnV = Glow;
			 	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			 	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
}

void Decode_CI_Msg(msg)
{
	switch(msg->data[0])
		{
		case LED_RED: Set_red_LED();
			break;
		case LED_BLUE:Set_blue_LED();
			break;
		case LED_GREEN:Set_green_LED();
			break;
		//case LED_DANCE:Set_LED_config();
			//break;
		}
}

void UART0_IRQHandler()
{
	__disable_irq();

	char receive;
	receive= UART0->D;

	if(receive!='\r')
	{

	}

	if(receive='\r')
	{
		UART0->C2=0x00;
	}

	__enable_irq();
}


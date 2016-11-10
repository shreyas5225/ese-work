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
volatile int count1=0;
int Glow = 500;
FRDM_Cmd new;

int flag=0;
int flag1=0;
uint8_t array[10];
uint8_t array1[15]="Checksum Error";

void UART0_init(void)   //initialization function for UART
{

	__disable_irq();
	    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

		PORTA->PCR[2]= PORT_PCR_MUX(2);
		PORTA->PCR[1]= PORT_PCR_MUX(2);

		UART0->C2 = 0x00;
		UART0->C1 = 0x00;
		UART0->BDH = 0x00;
		UART0->BDL = 0x17;
		//UART0->C4 = 0x0F;

		//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
		UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
		UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RE_MASK;//(UART_C2_TE_MASK | UART_C2_RE_MASK );

		__enable_irq();
	    NVIC_EnableIRQ(UART0_IRQn);
		//NVIC->ISER[0] |= 0x00001000;


}

void Initialize_LED()					//initialization function for LED
{
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM2_BASE_PTR->MOD = 1875;
    TPM0_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM0_BASE_PTR->MOD = 1875;

    SIM_BASE_PTR->SCGC5 |=  0x400;
    SIM_BASE_PTR->SCGC5 |= 0x1000;
    PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);
    PORTD_BASE_PTR->PCR[1]=PORT_PCR_MUX(4);

    TPM2_BASE_PTR->CONTROLS[0].CnSC =  0x20 | 0x4;
    TPM2_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
    TPM0_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
}


void structure_init (FRDM_Cmd *msg)     // initialization function for structure
{
	msg->command= array[0]-48;
	msg->length= array[1]-48;
	msg->data= array[2]-48;
	msg->checksum= array[3]-48;
	if(((msg->command)+(msg->length)+(msg->data))!=msg->checksum)
	{
			flag1=1;
			count1=0;
			count=0;
			UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK );
			UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;


		}
	else
	{
	Decode_CI_Msg(&msg);
	count= 0;
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	}

}


void Set_red_LED()                              // red colour
{
	 	    TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    TPM2_BASE_PTR->CONTROLS[0].CnV = Glow;
}


void Set_blue_LED()                             //blue colour
{

			TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
			TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			TPM0_BASE_PTR->CONTROLS[1].CnV = Glow;

}

void Set_green_LED()							//green colour
{
				TPM2_BASE_PTR->CONTROLS[1].CnV = Glow;
			 	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			 	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
}

void Decode_CI_Msg(FRDM_Cmd *msg)                // decode message
{
	switch((msg->data))
		{
		case LED_RED: Set_red_LED();
			break;
		case LED_BLUE:Set_blue_LED();
			break;
		case LED_GREEN:Set_green_LED();
			break;

		}
}

void UART0_IRQHandler()					// UART IRQ handler
{
	__disable_irq();

	char receive;
	uint8_t state;
	state= UART0->S1;

	if(state & UART_S1_RDRF_MASK)
	{
		receive= UART0->D;
	if(receive!='\r')
	{
		*(array+count)= receive;
		count++;
	}

	else
	{
		UART0_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_RIE_MASK);
		flag= 1;
		receive = UART0->D;
	}
  }

	if((state & UART_S1_TDRE_MASK) && (flag1==1))
		{
			if((*(array1+counter1))!='\0')
			{
				UART0->D = *(array1 + counter1);
				count1++;
			}
			else
			{
				UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TE_MASK);
				UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TIE_MASK);
				flag1=0;
			}
		}

	__enable_irq();
}

int main()
{
	Initialize_LED();
	UART0_init();

	while(1)
	{
		if(flag==1)
		{
			structure_init(&new);
			flag=0;
		}
	}
	return 0;
}


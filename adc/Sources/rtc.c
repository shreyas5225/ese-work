/*
 * rtc.c
 *
 *  Created on: Dec 6, 2016
 *      Author: shva9978
 */
/*
#include <stdio.h>
#include "MKL25Z4.h"
#include "rtc.h"
#include "stdint.h"
#include "zero.h"
#include "ftoa.h"



int seconds = 0,time = 0,minutes = 0;
//uint8_t interrupt = 0;

void rtc_clock()
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK;

	MCG_C2 &= ~(MCG_C2_IRCS_MASK);

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTC_PCR1 |= (PORT_PCR_MUX(1));

	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);

	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL (0b100);

	PORTC_PCR3 |= PORT_PCR_MUX(5);
}

void rtc_init()

{
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	RTC_CR |= RTC_CR_SWR_MASK;

	RTC_CR &= ~(RTC_CR_SWR_MASK);

	if (RTC_SR & RTC_SR_TIF_MASK)
	{
		RTC_TSR = 0x00000000;
	}

	RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

	NVIC_EnableIRQ(RTC_Seconds_IRQn);

	//NVIC_EnableIRQ(RTC_Seconds_IRQN - 16);

	RTC_IER |= RTC_IER_TSIE_MASK;

	RTC_SR |= RTC_SR_TCE_MASK;

	RTC_TSR = 0xFF;

}


void RTC_Seconds_IRQHandler(void)
{
	//interrupt = 1;

	seconds = RTC_TSR;
	minutes = (seconds/60);
    if (seconds >59)
    {
    	minutes+=1;
    	RTC_SR &= ~RTC_SR_TCE_MASK;
    	RTC_TSR = 0x00; //Reset counter
    	seconds = RTC_TSR;
    	RTC_SR |= RTC_SR_TCE_MASK;
    }
    time= (minutes+(seconds/100));
}




//void alarm (int minutes, int seconds)
//{
//	alarmseconds = minutes*60 + seconds;
//	RTC_TAR = alarmseconds;
//	NVIC_EnableIRQ(RTC_IRQn);
//	RTC_IER |= RTC_IER_TAIE_MASK;
//}

int main()
{
	UART0_init();

	rtc_clock();
	__enable_irq();
	rtc_init();

	while(1)
		{
		uint16_t len=0;
		char transfer[20];
		char *b=transfer;
	print_stringl("\n\rTimer value:");
	ftoa(minutes, transfer, 2);
			while(*b!='\0')
			 {
				 len++;
				 b++;
			 }
			print_string(transfer, len);
		}
			return 0;
}

*/

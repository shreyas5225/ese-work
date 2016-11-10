/*
 * timer.c
 *
 *  Created on: 02-Nov-2016
 *      Author: Shreyas
 */

#include "MKL25Z4.h"
#include "timer.h"
#include "uart.h"

volatile uint32_t count = 0;
uint32_t a = 0;
uint32_t b =0;

void profiler_start()   // profiler start function
{
				SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
				SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 */
				TPM0->SC = 0; /* disable timer while configuring */
				TPM0->SC = 0x00; /* prescaler /1 */
				TPM0_MOD = 0x1E0;

				TPM0->SC |= 0x80; /* clear TOF */
				TPM0_SC |= TPM_SC_TOIE_MASK;
				NVIC_EnableIRQ(TPM0_IRQn); /* enable IRQ17 (bit 17 of ISER[0]) */
				//NVIC_EnableIRQ(DMA0_IRQn);

				TPM0->SC |= 0x40; /* enable timeout interrupt */
				TPM0->SC |= 0x08; /* enable timer */


}


void profiler_stop()   // profiler stop function
{
	NVIC_DisableIRQ(TPM0_IRQn);
	//Disable the counter
	TPM0_SC = 0;
	TPM0_CONF = 0;
	a = count*480 + TPM0_CNT;
	b=a;
}

void TPM0_IRQHandler()      // TPM IRQHandler
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		TPM0_SC |= TPM_SC_TOF_MASK;
		count++;
	}
}



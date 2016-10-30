/*
 * dma.c
 *
 *  Created on: 26-Oct-2016
 *      Author: Shreyas
 */

#include "dma.h"
#include "MKL25Z4.h"


volatile uint32_t count = 0;




void init_DMA_1Trans(void)

{

	uint32_t a = 0;
	uint32_t b =0;
	unsigned char g8bSource[10]= {0,1,2,3,4,5,6,7,8,9};
	unsigned char g8Destiny[10]= {1,0,0,0,0,0,0,0,0,0};

			SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
			SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(49);

			DMA_SAR0 = (uint32_t)&g8bSource;
			DMA_DSR_BCR0 |= 0x20u;
			DMA_DCR0 |= DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);

			DMA_DCR0 |= DMA_DCR_SINC_MASK;
			DMA_DCR0 |= DMA_DCR_DINC_MASK;

			DMA_DAR0 = (uint32_t)&g8Destiny;

			SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
			SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 */
			TPM0->SC = 0; /* disable timer while configuring */
			TPM0->SC = 0x00; /* prescaler /1 */
			TPM0_MOD = 0x64;
			//TPM0->SC |= 0x80; /* clear TOF */
			TPM0_SC |= TPM_SC_TOIE_MASK;
			TPM0->SC |= 0x40; /* enable timeout interrupt */
			TPM0->SC |= 0x08; /* enable timer */
			NVIC_EnableIRQ(TPM0_IRQn); /* enable IRQ17 (bit 17 of ISER[0]) */
			NVIC_EnableIRQ(DMA0_IRQn);
			DMA_DCR0 |= DMA_DCR_START_MASK;

			a = count*480 + TPM0_CNT;
			b=a;

}


void TPM0_IRQHandler()
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		TPM0_SC |= TPM_SC_TOF_MASK;
		count++;
	}
}

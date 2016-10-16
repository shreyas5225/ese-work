#include "MKL25Z4.h"
#include "memory.h"
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "mcg.h"

void profiler_start(void);
void profiler_stop(void);

#define data 5000

volatile uint32_t count = 0;

uint32_t main(void)
{
	initialize_pll(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);
	uint32_t a = 0;
	double b = 0;

	uint8_t src[data];
	uint32_t length;
	length = data;
	uint8_t dst[data];

	profiler_start();
	my_memmove(src, dst, length);
	profiler_stop();

	a = count*480 + TPM0_CNT;
	b = (a / 48000000.00);

	send_char(a);
	return 0;
}


void send_char(int c)
	{
		while(!(UART0->S1 & 0xC0))
		 {

		 }
		 UART0->D = c;

	}


void profiler_start()
{
	// PLL clock select
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);

	// Select MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Nullify the control registers to ensure counter is not running

	TPM0_SC = 0;
	TPM0_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM0_SC = TPM_SC_PS(0);

	//Enable Interrupts for the Timer Overflow
	TPM0_SC |= TPM_SC_TOIE_MASK;

	// Setting modulo value to set 10us as the execution timer
	TPM0_MOD = 480;

	//Enable the TPM COunter
	TPM0_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
	//enable_irq(INT_TPM0 - 16);

}

void profiler_stop()
{
	NVIC_DisableIRQ(TPM0_IRQn);
	//Disable the counter
	TPM0_SC = 0;
	TPM0_CONF = 0;
}

void TPM0_IRQHandler()
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		TPM0_SC |= TPM_SC_TOF_MASK;
		count++;
	}
}

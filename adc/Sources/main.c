/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



/*
#include <MKL25Z4.h>

void ADC0_init(void);
void LED_set(int s);
void LED_init(void);

void ADC0_init(void)
{
SIM->SCGC6 |= 0x8000000; // clock to ADC0
ADC0->SC2 &= ~0x40; // software trigger
// clock div by 4, long sample time, single ended 12 bit, bus clock
ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void LED_init(void)
{
SIM->SCGC5 |= 0x400; // enable clock to Port B
SIM->SCGC5 |= 0x1000; // enable clock to Port D
PORTB->PCR[18] = 0x100; // make PTB18 pin as GPIO
PTB->PDDR |= 0x40000; // make PTB18 as output pin
PORTB->PCR[19] = 0x100; // make PTB19 pin as GPIO
PTB->PDDR |= 0x80000; // make PTB19 as output pin
PORTD->PCR[1] = 0x100; // make PTD1 pin as GPIO
PTD->PDDR |= 0x02; // make PTD1 as output pin
}

void LED_set(int s)
{
if (s & 1) // use bit 0 of s to control red LED
PTB->PCOR = 0x40000; // turn on red LED
else
PTB->PSOR = 0x40000; // turn off red LED
if (s & 2) // use bit 1 of s to control green LED
PTB->PCOR = 0x80000; // turn on green LED
else
PTB->PSOR = 0x80000; // turn off green LED
if (s & 4) // use bit 2 of s to control blue LED
PTD->PCOR = 0x02; // turn on blue LED
else
PTD->PSOR = 0x02; // turn off blue LED
}

void UART0_init(void)
	{
		SIM->SCGC4 |= 0x400;
		SIM->SOPT2 |= 0x4000000;

		UART0->C2 = 0;
		UART0->BDH = 0x00;
		UART0->BDL = 0x17;
		UART0->C4 = 0x0F;
		UART0->C1 = 0x00;
		UART0->C2 = 0x08;

		SIM->SCGC5 = 0x0200;
		PORTA->PCR[2]= 0x0200;
	}

void send_char(char c)
	{
		while(!(UART0->S1 & 0xC0))
		  {

		  }
		  UART0->D = c;

	}

void send_string(char s[])
{
		int i=0;

		while (s[i] != 0x00)
		{
			send_char(s[i]);
			i++;
		}

}

void LOG_0(char * data, int len) //LOG 0 function
{

	send_string(data);	//printing the string through UART
	int i;
	    for(i=0;i<len;i++)
	    {
	        printf("%c",data[i]);	//print the final string
	    }

}



int main (void)
{
short int result;
char char_array[] = {"\n\rThe temperature is:"};
LED_init(); // Configure LEDs
ADC0_init(); // Configure ADC0
UART0_init();
int temp;
while (1)
{
ADC0->SC1[0] = 26; // start conversion on channel 26 temperature
while(!(ADC0->SC1[0] & 0x80))
{ } // wait for COCO
result = ADC0->R[0]; // read conversion result and clear COCO flag
LED_set(result); // display result on LED
result = result * 0.0029296875; //Convert the ADC reading into voltage
if (result >= 0.7012)//Check for Hot or Cold Slope
	{
		result = 25 - ((result - 0.7012)/(0.001749));
	}
	else
	{
	     result = 25 - ((result - 0.7012)/(0.001749));
	}
   LOG_0(&char_array,result);
}
}
*/


/*void UART_temp()
{

}
*/

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

#include "MKL25Z4.h"
#include "circbuff.h"
#include "led.h"
#include "uart.h"
#include "compiler_switch.h"
#include "circular_buffer_test.h"
#include "log.h"
#define test_function 1
int main(void)
{
	__disable_irq();				// disable interrupts

	UART0_init();					//initialize UART0 function
	__enable_irq();					// enable interupts again
	uint8_t tx_str[100]="For echo mode enter t, for led brightness change enter w or s,for color change enter a or d",rx_str[100]="0";
	put_data_intr(tx_str);
	Initialize_LED();			//	initialize the LED
	uint32_t i=0;

	   //test function
#ifndef test_function
		    void initialize_test(void);
		    void buff_full_test(void);
		    void buff_empty_test(void);
		    void add_data_test(uint8_t itemtoadd);
		    void remove_data_test(void);
#endif


#ifndef Log_function				// initialize the testing strings for log function

		  	char string1[]="Testing123, Serial Print Test, no params";
		    char string2[]="This is an integer number:";
		    char string5[]="This is a floating point number:";
		    float var2=200;
		    float var3=4096;
		    float var4=123456;
		    float var5=1543.321;

	#if A   //FRDM UART
	    LOG_0(&string1,40);

	    send_char('\r\n');
	    send_char('\r');

	    LOG_1(&string2,var2,0);

	    send_char('\r\n');
	    send_char('\r');

	    LOG_1(&string2,var3,0);

	    send_char('\r\n');
	    send_char('\r');

	    LOG_1(&string2,var4,0);

	    send_char('\r\n');
	    send_char('\r');

	    LOG_1(&string5,var5,3);

	    send_char('\r\n');
	    send_char('\r');

	    delayMs(200);
	#endif

	#if B   //BBB PRINTF

	    LOG_0(&string1,40);
	    printf("\n\n");

	    LOG_1(&string2,var2,0);
	    printf("\n");

	    LOG_1(&string2,var3,0);
	    printf("\n");

	    LOG_1(&string2,var4,0);
	    printf("\n");

	    LOG_1(&string5,var5,3);
	    printf("\n");

	#endif


#endif

	while(1)
	{
		state ec=empty_buff(&rx_buf);

		if(ec==buffer_not_empty )
		{
			uint8_t con=remove_data_buff(&rx_buf),mode;
			if(con=='t' || con==0xd)
			{
				mode=con;

			}

			if(mode=='t')
			{
				rx_str[i] = con;
				i++;
			}
		    else if(mode==0xd)
			{
			    mode=0;
			    i=0;
			    put_data_intr(rx_str);
			}
		    else if((con=='a'|| con=='s' || con=='w' || con=='d'))
		    {
		    	Change_LED(con);

		    }
		}

	}

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

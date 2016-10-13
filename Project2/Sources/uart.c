
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuff.h"

//send char through UART
void send_char(char c)				// send characters by each bit
    {
        while(!(UART0->S1 & 0xC0));
          UART0->D = c;

    }
void send_string(char s[])			//send string after each charcters
{
        int i=0;

        while (s[i] != '\0')
        {
            send_char(s[i]);
            i++;
        }

}
void UART0_init(void)				// initialize the UART0 condition
{
		SIM->SCGC4 |= 0x0400;				// check for clock source
		SIM->SOPT2 |= 0x04000000;          // take clock source from the FLL clock

		UART0->C2 = 0;
		UART0->BDH = 0x00;               // initialize the baud rate
		UART0->BDL = 0x17;
		UART0->C4 = 0x0F;                // set sampling ratio
		UART0->C1 = 0x00;					// set 8 bit
		UART0->C2 = 0x08|0x24;

		SIM->SCGC5 = 0x0200;
		PORTA->PCR[2]= 0x0200;				// turn on transmit pin
		PORTA->PCR[1]= 0x0200;				// tirn  on receive pin
		tx_buf.buff = initialize_buff(&tx_buf);
			tx_buf.head=buff_ptr;
					 	tx_buf.tail=buff_ptr;
					 	tx_buf.buff=buff_ptr;
					 	tx_buf.new_len= 0;
					 	tx_buf.length = MAX_LEN;
		    rx_buf.buff = initialize_buff(&rx_buf);
		    rx_buf.head=buff_ptr;
					rx_buf.tail=buff_ptr;
					rx_buf.buff=buff_ptr;
					rx_buf.new_len= 0;
					rx_buf.length = MAX_LEN;
NVIC->ISER[0] |= 0x00001000;
NVIC_SetPriority(UART0_IRQn,2);
}

void delayMs(int n)
   {
	int i;
	int j;
	for (i=0;i<n;i++)
	for (j=0;j<n;j++){}
   }


uint8_t da=0;

void UART0_IRQHandler()
{
state error_code = full_buff(&rx_buf);
if((UART0_S1 & (UART0_S1_RDRF_MASK)) && error_code==buffer_not_full)
{
	uint8_t mode;
	uint32_t i;
	da= UART0->D;
	add_data_buff(&rx_buf,da);
}

else if(error_code==buffer_empty)
	{
		UART0_C2 &= ~UART0_C2_RIE_MASK;
	}


	 error_code =empty_buff(&tx_buf);
	// If buffer is not empty and TDRE flag is set then transmit the character
	if((UART0_S1 & (UART0_S1_TDRE_MASK))&& error_code==buffer_not_empty)
	{

		UART0_D =  remove_data_buff(&tx_buf);
	}
	else if(error_code==buffer_empty)
	{
		UART0_C2 &= ~UART0_C2_TIE_MASK;
	}

}


void put_data_intr(uint8_t *c)
{
	uint8_t j=0;
	uint32_t i=0;
	while(*(c+i) !='\0')
	{
	j = add_data_buff(&tx_buf,*(c+i));
	i++;
	}
	UART0_C2 |= UART0_C2_TIE_MASK;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuff.h"

cirbuf_t *cb1;

void initialize_test(void)
{
	//uint8_t *buff;
	char passstring1[50]="CB UNIT TEST: 1/5-<initialize>....PASS\n\r";
//	cb->buff=initialize(&cb);
	initialize_buffer(&cb1);

	send_string(passstring1);
}

//uint8_t*initialize(cirbuf_t *cb)
void initialize_buffer(cirbuf_t *cb1)
{

	cb1->buff=malloc(sizeof(cirbuf_t));
	buff_ptr = (uint8_t*) calloc(1 , sizeof(uint8_t));
	cb1->head=buff_ptr;
	cb1->tail=buff_ptr;
}

void buff_full_test(void)
{
	int val;
	char passstring2[50]="CB UNIT TEST: 2/5-<initialize>....PASS\n\r";
	char failstring2[50]="CB UNIT TEST: 2/5-<initialize>....FAIL\n\r";
	val=buff_full(&cb1);

	if(val==0)
	{
		send_string(passstring2);
	}
	else if(val==1)
	{
		send_string(failstring2);
	}
}

void buff_empty_test(void)
{
	int val;
	char passstring3[50]="CB UNIT TEST: 3/5-<buff_empty>....PASS\n\r";
	char failstring3[50]="CB UNIT TEST: 3/5-<buff_empty>....FAIL\n\r";
	val=buff_empty(&cb1);

	if(val==2)
	{
		send_string(passstring3);
	}
	else if(val==3)
	{
		send_string(failstring3);
	}
}

void add_data_test(uint8_t itemtoadd)
{
	int val;
	char passstring4[50]="CB UNIT TEST: 4/5-<add_data>....PASS\n\r";
	char failstring4[50]="CB UNIT TEST: 4/5-<add_data>....FAIL\n\r";
	val=add_data(&cb1, itemtoadd);

	if(val==4)
	{
		send_string(passstring4);
	}
	else if(val==5)
	{
		send_string(passstring4);
	}
	else if(val==0)
	{
		send_string(failstring4);
	}
}

void remove_data_test(void)
{
	int val;
	char passstring5[50]="CB UNIT TEST: 5/5-<remove_data>....PASS\n\r";
	char failstring5[50]="CB UNIT TEST: 5/5-<remove_data>....FAIL\n\r";
	val=remove_data(&cb1);

	if(val!=-1)
	{
		send_string(passstring5);
	}
	else if(val==-1)
	{
		send_string(failstring5);
	}
}

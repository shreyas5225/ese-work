

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
//#include "MKL25Z4.h"


uint8_t* initialize_buff(cirbuf_t *cb1)      //initialize memory allocation for buffer
{
	cb1= malloc(sizeof(cirbuf_t));
	buff_ptr = (uint8_t*) calloc(1 , sizeof(uint8_t));
    return cb1->buff;
}

void destroy_buff(cirbuf_t *cb1)		//destroy memory allocated for the buffer
{
	free(cb1);
}


state full_buff(cirbuf_t *cb1)			//check condition for buffer full
{
    if (cb1->new_len == cb1->length)
    {
        return buffer_full;
    }
    else
    {
        return buffer_not_full;
    }

}

state empty_buff(cirbuf_t *cb1)		//check condition for buffer empty
{
    if(cb1->new_len==0)
    {
        return buffer_empty;
    }
    else
    {
        return buffer_not_empty;
    }
}

state add_data_buff(cirbuf_t *cb1, uint8_t item)  // add data into the buffer
{
												//check buffer status first
    state code;
    code=full_buff(cb1);						//check for wrap around condition
    if(code==buffer_not_full)
    {
        if(cb1->head==(cb1->buff)+(cb1->length)-1)
        {
          cb1->head=cb1->buff;
        *(cb1->head)=item;
        (cb1->new_len)++;
        return  add_successwithwrap;
        }

        else								// else add normally
        {
            cb1->head++;
            *(cb1->head)=item;
            (cb1->new_len)++;
            return  add_success;

        }


    }
    else if(code==buffer_full)
    {
      return buffer_full;
    }

}

uint8_t remove_data_buff(cirbuf_t *cb1)			// check for buffer data removal
{
    state code;
	uint8_t rd;
    code=empty_buff(cb1);
    if(code==buffer_not_empty)			//check for buffer status first
    {

        if(cb1->tail==((cb1->buff)+(cb1->length))-1)
        {

        cb1->tail=cb1->buff;					//check for tail status before removal
		rd=*(cb1->tail);
        *(cb1->tail)=0;
        (cb1->new_len)--;
        return rd;
        }

        else
        {										//remove data using tail
            (cb1->tail)++;
			rd=*(cb1->tail);
            *(cb1->tail)=0;
            (cb1->new_len)--;
            return rd;

        }
    }
    else if(code==buffer_empty)
    {
      return buffer_empty;
    }
}

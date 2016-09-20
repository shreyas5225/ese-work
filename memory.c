#include "memory.h"
#include <stdio.h>
#include <stdint.h>

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{

	int i;					/* For incrementing */


        if(dst==src)			/* check if source and destination are pointing at the same location */
        {
                printf("Error. Overlap occurs\n");	/* if yes, print error as overlap occurs */
                return 1;			/* return error value */
        }

        else if(dst<src)	/* check if destination is before source */
        {
                for(i=0;i<length-1;i++)		/* if yes, move data accordingly */
                {
                        *(dst+i)=*(src+i);
                }
        return 0;			/* return non-error value */
        }

        else
        {
                for(i=length-1;i>=0;i--)  /* if destination is after source, move data accordingly */
                {
                        *(dst+i)=*(src+i);
                }
        return 0;		/* return non-error value */
        }
}

int8_t my_memzero(uint8_t *src, uint32_t length)
{
        uint8_t *s; /* take pointer */re
        uint8_t zero=0; /* take zero value to put */
        s=src;
        uint8_t *end=s+length;	/* assign the end of the memory location */

        while(s!=end)	/* input value zero at the memory location */
        {
                *s=zero;
                s++;
        }

return 0; /* return non-error value */
}

int8_t my_reverse(uint8_t *str, uint32_t length)
{
	int start=0;	/* initialize start index */ 
	int end=length-1;	/* initialize end index */
	char *st;
	st=(char*)str;	/* assign pointer */

	while(start<end)	/* perform reverse operation */
	{	
        	char temp=*(st+start);
        	*(st+start)=*(st+end);
        	*(st+end)=temp;
        	start++;
        	end--;
	}

	return *str; /* return reversed data */
}

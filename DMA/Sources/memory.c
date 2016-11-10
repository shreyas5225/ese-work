
#include <stdio.h>
#include "memory.h"
#include <stdint.h>

void  my_memmove(uint8_t *source,uint8_t *destination,uint32_t length)
{
        int i = 0;
        uint8_t *src = (uint8_t *)source;
        uint8_t *dest = (uint8_t *)destination;
        if(src == dest) {
        printf("Same string, same address\n");
        }
	else if(dest<src)
        {
		for( i = 0; i < length; i++)
		{
		        *(dest + i) = *(src + i);
		}
	printf("dest is %p\n",dest);
        }
	else
	{
		for(i=length-1;i>=0;i--)
		 *(dest + i) = *(src + i);
		printf("dest is %p\n",dest);
	}

}

#if MEMZERO
void my_memzero(uint8_t *src, uint32_t length)
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
 }
#endif

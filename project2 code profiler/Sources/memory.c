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



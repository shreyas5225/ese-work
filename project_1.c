#include "project_1.h"
#include <stdio.h>
#include <stdint.h>

void project_1_report()
{
	uint8_t array[32];
	uint8_t *aptr_1=array;
	uint8_t *aptr_2=(array+8);
	uint8_t *aptr_3=(array+16);
	int i;

	for(i=0;i<16;i++)
	{
		*(aptr_1+i)=31+i;
	}

	if(my_memzero((aptr_3+1),16)!=0)
	{
	printf("Error. Memzero function failed\n");
	}

	printf("\n\nPointer locations:\naptr_1=%d\naptr_2=%d\naptr_3=%d",aptr_1,aptr_2,aptr_3);

   	printf("\nArray elements after initialization:\n");

   	for(i=0;i<32;i++)             /* Printing array elements */
	{	
		printf("%d\t",array[i]);
	}

	 printf("\n\nPointer locations:\naptr_1=%d\naptr_2=%d\naptr_3=%d",aptr_1,aptr_2,aptr_3);

   printf("\nArray elements before move and reverse\n");

       for(i=0;i<32;i++)           /* Printing array elements */
	{
		printf("%d\t",array[i]);
	}

	if(my_memmove(aptr_1,aptr_3,8)!=0)
	{
		printf("Error. Memmove function failed\n");
	}

	if(my_memmove(aptr_2,aptr_1,16)!=0)
        {
                printf("Error. Memmove function failed\n");
        }

	my_reverse(aptr_1,32);
	
	printf("\n\nPointer locations:\naptr_1=%d\naptr_2=%d\naptr_3=%d",aptr_1,aptr_2,aptr_3);

   printf("\nArray elements after reversing entire 32 on aptr_1\n");
	for(i =0;i<32;i++)           /* Printing array elements */
	{
		printf("%d\t",array[i]);
	}

	
	printf("\n");
return 0;

}

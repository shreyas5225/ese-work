#include "hw1.h"
#include<stdio.h>

char reverse_string(char *str, int length)
{
 int k;
 char *begin,*end,temp;
 

 if(length==0)
 {
   printf("Enter a correct string\n");

  return 1;

 }


 if(*str=='\0')
 {
   printf("Enter string with characters\n");
   return 1;

 }



 begin = str;
 end = str;

 for ( k = 0 ; k < ( length - 1 ) ; k++ )
 end++;
 for ( k = 0 ; k < length/2 ; k++ )
 {
  temp = *end;
  *end = *begin;
  *begin = temp;
   begin++;
   end--; 
 }
return * str;
}

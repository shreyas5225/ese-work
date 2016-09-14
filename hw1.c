#include "hw1.h"
#include<stdio.h>

char reverse_string(char *str, int length)
{
 int k;
 char *begin,*end,temp;
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

}

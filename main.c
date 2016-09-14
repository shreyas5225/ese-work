#include<stdio.h>
#include<string.h>
#include "hw1.h"
 int main() 

{

	char string[100],ch;

	int len,i;



   printf("Enter a string\n");

   while(ch!='\n')
   {
      ch=getchar();
      string[i]=ch;
      i++;
   }
   
   string[i]='\0';
    
   len= strlen(string); 

   reverse_string(string,len);

 

   printf("Reverse of entered string is %s\n", string);

  
   return 0;
}



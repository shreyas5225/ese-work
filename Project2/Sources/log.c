/*
 * log.c
 *
 *  Created on: Oct 12, 2016
 *      Author: shva9978
 */


#include "MKL25Z4.h"
#include <stdio.h>
#include "log.h"
#include "uart.h"
#include "compiler_switch.h"

void reverse(char *str, int len)      // string reverse function
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int intToStr(int x, char str[], int d)			// convert characters from interger to string
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
    while (i < d)
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

char ftoa(float n, char *res, int afterpoint)		// convert float to ascii by seperating integer and fractional part
{
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
void LOG_0(char * data, int len)				//log 0 function to test strings without parameters
{
#if A
	send_string(data);
#endif

#if B
    int i;
    for(i=0;i<len;i++)
    {
        printf("%c",data[i]);
    }
#endif
}
void LOG_1(char * data, float param,int point)  //log 1 function to test strings with parameters
{
    char floatchar[50];
    char *f=floatchar;
    int length,i=0,j=0,z=0;

    ftoa(param,&floatchar,point);

    for(i=0;data[i]!='\0';++i);
    z = i;
    for(j=0;floatchar[j]!='\0';++j,++i)
    {
        data[i]=floatchar[j];
    }

    data[i]='\0';

    for(length=0;data[length]!='\0';length++);
    LOG_0(data,length+1);

    for(j=0;floatchar[j]!='\0';++j,++z)
        {
            data[z]='\0';
        }

}






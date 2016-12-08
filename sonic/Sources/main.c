/*
#include "MKL25Z4.h"
#include <stdint.h>

#define DB0	PORTD_PCR0 |= PORT_PCR_MUX(1);
#define DB1	PORTD_PCR1 |= PORT_PCR_MUX(1);
#define DB2	PORTD_PCR2 |= PORT_PCR_MUX(1);
#define DB3	PORTD_PCR3 |= PORT_PCR_MUX(1);
#define DB4	PORTD_PCR4 |= PORT_PCR_MUX(1);
#define DB5	PORTD_PCR5 |= PORT_PCR_MUX(1);
#define DB6	PORTD_PCR6 |= PORT_PCR_MUX(1);
#define DB7	PORTD_PCR7 |= PORT_PCR_MUX(1);

#define E PORTC_PCR4 |= PORT_PCR_MUX(1);
#define RS PORTC_PCR5 |= PORT_PCR_MUX(1);
#define RW PORTC_PCR6 |= PORT_PCR_MUX(1);

char out_1[6];
char p_1[5];
unsigned long duration_1 = 0;

char out_2[6];
char p_2[5];
unsigned long duration_2 = 0;

char out_3[6];
char p_3[5];
unsigned long duration_3 = 0;

int flag1=0;
int flag2=0;
int flag3=0;

int count1=1;
int count2=1;
int count3=1;

char a,i,read[15];

void delay_ms(int n)
{
	int i,a;

	a=n/47.68;

	for(i=0;i<a*1000000;i++);
}

void delay_us(int m)
{
	int i,a;

	a=m/47.68;

	for(i=0;i<a*1000;i++);
}

void TOGGLE_EPIN(void)
{
	delay_us(500);
	GPIOC_BASE_PTR->PDOR |= 0x00000010;	//SET E HIGH
    delay_us(500);
    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET E LOW
    delay_us(500);
}

void InitPins()
{
	GPIOD_BASE_PTR->PDOR |= 0x00000000;	//SET LOW PORT D

	GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET LOW PORT C
}

void NewLine()
{
	GPIOC_BASE_PTR->PDOR |= 0x00000060;	//SET RS and RW HIGH

	GPIOD_BASE_PTR->PDOR |= 0x000000C0;	//SET DB7 and DB6 HIGH

	TOGGLE_EPIN();
}

void ClearDisplay()
{
	GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW

	GPIOD_BASE_PTR->PDOR |= 0x00000001;	//SET DB0 HIGH

	TOGGLE_EPIN();
}

void LCDInit(void)
{
   // E_Write(0);

	delay_ms(100);

	GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
	GPIOD_BASE_PTR->PDOR |= 0x00000030;	//SET DB4 and DB5 HIGH

    TOGGLE_EPIN();

    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000030;	//SET DB4 and DB5 HIGH

    TOGGLE_EPIN();

    delay_us(100);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000030;	//SET DB4 and DB5 HIGH

    TOGGLE_EPIN();


    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000038;	//SET DB3, DB4 and DB5 HIGH

    TOGGLE_EPIN();

    //Display off
    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000008;	//SET DB3 HIGH

    TOGGLE_EPIN();

    // Display on/off control
    delay_ms(100);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x0000000C;	//SET DB3 HIGH

    TOGGLE_EPIN();

    // Entry mode set
    delay_ms(100);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000006;	//SET DB1 and DB2 HIGH

    TOGGLE_EPIN();

    //Display clear
    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000001;	//SET DB0 HIGH

    TOGGLE_EPIN();

    //Entry mode set
    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000006;	//SET DB1 and DB2 HIGH

    TOGGLE_EPIN();

    //OPERATION

// Function Set
    delay_ms(100);

    GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET RS and RW LOW
    GPIOD_BASE_PTR->PDOR |= 0x00000038;	//SET DB3, DB4 and DB5 HIGH

    TOGGLE_EPIN();
}

void ShowOnLCD(uint8_t value);

void StringOnLCD(char *str)
{
    uint8_t i,j=0,val,value[33];

    for(i=0;str[i] != '\0';i++)
    {
        value[j] = str[i];
        j++;
    }

   for(i=0;i<j;i++)
    {
        val = value[i];

        ShowOnLCD(val);
    }
}

void ShowOnLCD(uint8_t value)
{

    InitPins();

    delay_ms(5);

    GPIOC_BASE_PTR->PDOR |= 0x00000020;	//SET RS HIGH

    if(value & 0x80)
    {
        //DB7_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000001;	//SET DB0 HIGH
    }

    if(value & 0x40)
    {
        //DB6_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000002;	//SET DB1 HIGH
    }

    if(value & 0x20)
    {
        //DB5_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000004;	//SET DB2 HIGH
    }

    if(value & 0x10)
    {
        //DB4_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000008;	//SET DB3 HIGH
    }

    if(value & 0x08)
    {
        //DB3_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000010;	//SET DB4 HIGH
    }

    if(value & 0x04)
    {
        //DB2_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000020;	//SET DB5 HIGH
    }

    if(value & 0x02)
    {
        //DB1_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000040;	//SET DB6 HIGH
    }

    if(value & 0x01)
    {
        //DB0_Write(1);
    	GPIOD_BASE_PTR->PDOR |= 0x00000080;	//SET DB7 HIGH
    }
    TOGGLE_EPIN();
}

int main(void)
{
	//GPIOD_BASE_PTR->PDDR |= 0x00000001;	//SET AS OUTPUT PORT D
	//GPIOD_BASE_PTR->PDOR |= 0x00000001;	//SET LOW
	GPIOD_BASE_PTR->PDDR |= 0x000000FF;	//SET AS OUTPUT PORT D
	//GPIOD_BASE_PTR->PDOR |= 0x00000000;	//SET LOW

	GPIOC_BASE_PTR->PDDR |= 0x00000070;	//SET AS OUTPUT PORT C
	//GPIOC_BASE_PTR->PDOR |= 0x00000000;	//SET LOW

	InitPins();

	LCDInit();

	ClearDisplay();

	ShowOnLCD('A');

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
*/

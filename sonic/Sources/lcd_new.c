/*
 * lcd_new.c
 *
 *  Created on: Dec 7, 2016
 *      Author: srkh2686
 */


/* p3_1.c: Initialize and display “Hello” on the LCD using 8-bit data mode.
* Data pins use Port D, control pins use Port A.
* This program does not poll the status of the LCD.
* It uses delay to wait out the time LCD controller is busy.
* Timing is more relax than the HD44780 datasheet to accommodate the
* variations among the LCD modules.
* You may want to adjust the amount of delay for your LCD controller.
*/
#include <MKL25Z4.H>
#define RS 0x04 /* PTA2 mask */
#define RW 0x02 /* PTA1 mask */
#define EN 0x20 /* PTA5 mask */
#define ECHO 0x10 /* PTC4 mask */
#define TRIGGER 0x20 /* PTC5 mask */

void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);

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

 /*Delay n milliseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().*/

void delayMs(int n) {
	int i;

	for(i=0;i<19000;i++);
	/*int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++) { }*/
}

void delayUs(int n) {
	int i;

	for(i=0;i<19;i++);
}

unsigned long pulseIn_1(void) {

    unsigned long pulseWidth_1 = 0;
    unsigned long loopCount_1 = 0;
    unsigned long loopMax_1 = 5000000;

    // When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
    while (PTC->PDIR & 0x10) {
       // LED_Write(1);
        if (loopCount_1++ == loopMax_1) {
            return 0;
        }
        pulseWidth_1++;
    }

    // While the pin is *not* in the target state we make sure the timeout hasn't been reached.
    while (!(PTC->PDIR & 0x10)) {
      //  LED_Write(0);
        if (loopCount_1++ == loopMax_1) {
            return 0;
        }
    }

    // Return the pulse time in microsecond!
    return pulseWidth_1 * 2.36; // Calculated the pulseWidth++ loop to be about 2.36uS in length.
}

void LCD_init(void)
{
	SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
	PORTD->PCR[0] = 0x100; /* make PTD0 pin as GPIO */
	PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
	PORTD->PCR[2] = 0x100; /* make PTD2 pin as GPIO */
	PORTD->PCR[3] = 0x100; /* make PTD3 pin as GPIO */
	PORTD->PCR[4] = 0x100; /* make PTD4 pin as GPIO */
	PORTD->PCR[5] = 0x100; /* make PTD5 pin as GPIO */
	PORTD->PCR[6] = 0x100; /* make PTD6 pin as GPIO */
	PORTD->PCR[7] = 0x100; /* make PTD7 pin as GPIO */

	PTD->PDDR = 0xFF; /* make PTD7-0 as output pins */

	SIM->SCGC5 |= 0x0200; /* enable clock to Port A */

	PORTA->PCR[2] = 0x100; /* make PTA2 pin as GPIO */
	PORTA->PCR[1] = 0x100; /* make PTA1 pin as GPIO */
	PORTA->PCR[5] = 0x100; /* make PTA5 pin as GPIO */
	PTA->PDDR |= 0x26; /* make PTA 5, 1, 2 as output pins */

	delayMs(30); /* initialization sequence */
	LCD_command(0x30);
	delayMs(10);
	LCD_command(0x30);
	delayMs(1);
	LCD_command(0x30);
	LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
	LCD_command(0x08); /* set 8-bit data, 2-line, 5x7 font */
	LCD_command(0x0C); /* move cursor right */
	LCD_command(0x06); /* move cursor right */
	LCD_command(0x01); /* clear screen, move cursor to home */
}
void LCD_command(unsigned char command)
{
	PTA->PCOR = RS | RW; /* RS = 0, R/W = 0 */
	PTD->PDOR = command;
	PTA->PSOR = EN; /* pulse E */
	delayMs(0);
	PTA->PCOR = EN;
	if (command < 4)
	delayMs(4); /* command 1 and 2 needs up to 1.64ms */
	else
	delayMs(1); /* all others 40 us */
}
void LCD_data(unsigned char data)
{
	PTA->PSOR = RS; /* RS = 1, R/W = 0 */
	PTA->PCOR = RW;
	PTD->PDOR = data;
	PTA->PSOR = EN; /* pulse E */
	delayMs(0);
	PTA->PCOR = EN;
	delayMs(1);
}

void Ultrasonic_init()
{
	SIM->SCGC5 |= 0x0800; /* enable clock to Port C */
	PORTC->PCR[4] = 0x100; /* make PTC4 pin as GPIO */
	PORTC->PCR[5] = 0x100; /* make PTC5 pin as GPIO */
	PTC->PDDR |= 0x20; /* make PTC 5 output pin */
}
void trigger()
{
	PTC->PDOR |= 0x00;
	delayUs(2);
	PTC->PDOR |= 0x20;
	delayUs(10);
	PTC->PDOR |= 0x00;
	delayUs(2);
}

int main(void)
{
	Ultrasonic_init();
	LCD_init();
	LCD_command(1); /* clear display */

	LCD_command(0x80); /* set cursor at first line */
	LCD_data('H'); /* write the word */
	LCD_data('e');
	LCD_data('l');
	LCD_data('l');
	LCD_data('o');
	LCD_data(' ');

	LCD_command(0xD0);
	LCD_data('E');
	LCD_data('S');
	LCD_data('E');

	while(1)
	{
		trigger();

	//	delayMs(500);

		duration_1 = pulseIn_1();

		duration_1 = duration_1*0.017;
		//duration_1 = duration_1/6;

	//	delayMs(500);

		sprintf(out_1,"%04lu",duration_1);
		p_1[0]=out_1[0];
		p_1[1]=out_1[1]+4;
		p_1[2]='.';
		p_1[3]=out_1[2];
		p_1[4]=out_1[3];

		//delayMs(5);

		LCD_command(0x86);
		delayMs(10);
		LCD_data(p_1[0]);
		LCD_data(p_1[1]);
		LCD_data(p_1[2]);
		LCD_data(p_1[3]);
		LCD_data(p_1[4]);
		LCD_data(' ');

		delayMs(1);
	}
}

/*
 * led.c
 *
 *  Created on: Oct 11, 2016
 *      Author: shva9978
 */



#include "MKL25Z4.h"
#include <math.h>
#include "led.h"


Colour_LED Colour=OFF;
uint16_t  val=100;

void Initialize_LED()											// initilize LED control operation by setting clock source
{
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;					// check for LED clock source
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);  // make use of TPM2 for red and green and TPM0 for blue
    TPM2_BASE_PTR->MOD = 1875;
    TPM0_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM0_BASE_PTR->MOD = 1875;

    SIM_BASE_PTR->SCGC5 |=  0x400;
    SIM_BASE_PTR->SCGC5 |= 0x1000;
    PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);
    PORTD_BASE_PTR->PCR[1]=PORT_PCR_MUX(4);

      TPM2_BASE_PTR->CONTROLS[0].CnSC =  0x20 | 0x4;
      TPM2_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
      TPM0_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
}

void Change_LED(uint8_t Character) 				// initialize characters for led control
{
      if(Character=='w' && val<1000)  	 // use w and s for brightness increase and decrease
      {
    	  val+=100;

      }
      else if(Character=='s' && val>0)
       {
             val-=100;
        }

      else if(Character=='a')
            {									// use a for changing order of colors from red to white
    	  Colour++;
          	 if(Colour>=8)
          	 {
          		Colour=0;
          	 }

            }
      else if(Character=='d')			// use d for changing order of colors from white to red
             {
    	  Colour--;
               if(Colour<=0)
                {
            	   Colour=7;
                }
              }
      Change_Brightness(Colour, val);

}

Change_Brightness(Colour_LED Colour, uint16_t Brightness)
{
 if(Colour==RED)
    {
	TPM2_BASE_PTR->CONTROLS[0].CnV = Brightness;	// use RGB colors to switch between the different sets of colors
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;				// colors can be modified by turning on and off one or the other colors
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==YELLOW)
	{
	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==GREEN)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==CYAN)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
	else if(Colour==BLUE)
	{
	TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
	else if(Colour==MAGENTA)
	{
	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==WHITE)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->CONTROLS[0].CnV=TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	}
	else
	{
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM0_BASE_PTR->CONTROLS[1].CnV = 0;

	}
}

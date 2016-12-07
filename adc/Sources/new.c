/*
 * new.c
 *
 *  Created on: Nov 26, 2016
 *      Author: shva9978
 */


#include <MKL25Z4.h>
#include "stdint.h"

uint16_t adc_temperature(void)
 {
	 uint16_t calib=0,send=0;
SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;		//Enabling clock to ADC0

ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |  	// 10 bits mode
		  ADC_CFG1_ADICLK(1)|	// Input Bus Clock divided by 2 (20-25 MHz out of reset (FEI mode) / 2)
		  ADC_CFG1_ADIV(2)|      // Clock divide by 4 (2.5-3 MHz)
		  ADC_CFG1_ADLSMP_MASK) ;	// Selecting the long sample time

ADC0_SC3 |= ADC_SC3_AVGE_MASK |		// Enable HW average
				ADC_SC3_AVGS(3)   |		// Set HW average of 32 samples
				ADC_SC3_CAL_MASK;		// Start calibration process

	while(ADC0_SC3 & ADC_SC3_CAL_MASK){} // Wait for calibration to end

		calib += ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 +
				 ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
		calib /= 2;
		calib |= 0x8000; 	// Set MSB
		ADC0_PG = calib;
		calib = 0;
		calib += ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 +
				 ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
		calib /= 2;
		calib |= 0x8000;	// Set MSB
		ADC0_MG = calib;

		ADC0_CFG1 = 0; // Reset register

		ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |  	// 10 bits mode
						  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
						  ADC_CFG1_ADIV(1)|     // Clock divide by 2 (10-12.5 MHz)
						  ADC_CFG1_ADLSMP_MASK) ;	// Selecting the long sample time

ADC0_SC2 |= ADC_SC2_DMAEN_MASK;    // DMA Enable
ADC0_SC3 = 0; // Reset SC3
ADC0_SC1A = 0x1A;  // Select tempreture sensor as input in single ended mode
while(ADC0_SC2 & ADC_SC2_ADACT_MASK){}	 // Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)){}// Run until the conversion is complete
   dma_setup16(&ADC0_RA,&send,2);
	return send ; 						//returning the ADC hex result
 }


void temp_calc()
{
	while(1)
	{
		uint16_t raw=0, len=0;
		float Vtemp=0,Temp=0,Temp1=0,Temp2=0,Tempf=0;
		char transfer[20];
		char *b=transfer;
	raw = adc_temperature(); //storing 10-bit temperature value
	Vtemp = raw * 0.0029296875 ; //Convert the ADC reading into voltage
	if (Vtemp >= 0.7012)    //Check for Hot or Cold Slope
	{
		Temp1 = (Vtemp-0.7012)/0.001646;
		Temp = 25 - Temp1 ;      //Cold Slope
		Tempf = (Temp - 32)/1.8;  //F to C conversion
	}
	else
	{
		Temp2 = (Vtemp-0.7012)/0.001646;
		Temp = 25 - Temp2 ;   //Hot Slope)
		Tempf = (Temp - 32)/1.8;  //F to C conversion
	}
	print("\n\rTempreture:");
	ftoa(Tempf, transfer, 2);
		while(*b!='\0')
		  {
			  len++;
			  b++;
		  }
		print_string(transfer, len);
	}
}

void UART0_init(void)
	{
		SIM->SCGC4 |= 0x400;
		SIM->SOPT2 |= 0x4000000;

		UART0->C2 = 0;
		UART0->BDH = 0x00;
		UART0->BDL = 0x17;
		UART0->C4 = 0x0F;
		UART0->C1 = 0x00;
		UART0->C2 = 0x08;

		SIM->SCGC5 = 0x0200;
		PORTA->PCR[2]= 0x0200;
	}














int main()
{
	UART0_init();

	int temp1;

	temp1= adc_temperature();
	temp_calc();

	return 0;

}


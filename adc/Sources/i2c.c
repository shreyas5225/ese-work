/*
 * i2c.c
 *
 *  Created on: Nov 30, 2016
 *      Author: shva9978
 */



#include <stdio.h>
#include "MKL25Z4.h"
#include "i2c.h"


signed char result[20];
unsigned char MasterTrans ;
unsigned char SlaveID;



void i2c_init()
{
		SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Turn on clock to I2C0 module
		SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;		// Turn on clock to Port E module
		PORTE_PCR24 = PORT_PCR_MUX(5);			// PTE24 pin is I2C0 SCL line
		PORTE_PCR25 = PORT_PCR_MUX(5);			// PTE25 pin is I2C0 SDA line
		I2C0_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
		I2C0_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C0 module

}

void i2c_start()
{
	I2C0_C1 |= I2C_C1_TX_MASK;
	I2C0_C1 |= I2C_C1_MST_MASK;
}

void i2c_stop()
{
	I2C0_C1 &= ~I2C_C1_MST_MASK;
	I2C0_C1 &= ~I2C_C1_TX_MASK;
}


void i2c_wait()
{
	 while((I2C0_S & I2C_S_IICIF_MASK)==0)
	{

	}

	 I2C0_S |= I2C_S_IICIF_MASK;
}

void i2c_DisableAck()
{
	 I2C0_C1 |= I2C_C1_TXAK_MASK;
}

void i2c_RepeatStart()
{
	I2C0_C1 |= I2C_C1_RSTA_MASK;
}

void i2c_Rxmode()
{
	 I2C0_C1 &= ~I2C_C1_TX_MASK;
	 I2C0_C1 &= ~I2C_C1_TXAK_MASK;

}



void i2c_Transmission(unsigned char SlaveID,unsigned char Mode)
{
  if(Mode == MWSR)
  {
	  MasterTrans = MWSR;
  }

  else
  {
	  MasterTrans = MRSW;
  }

  SlaveID = (unsigned char) ACCEL_I2C_ADDR  <<1;

  SlaveID |= (unsigned char)MasterTrans;

  i2c_start();

  i2c_write_byte(SlaveID);
}

void delay()
{
	int n;
	for (n=0;n<100;n++);
}

unsigned char i2c_readregister(unsigned char Regaddress)
{
	unsigned char result;

	i2c_Transmission(SlaveID,MWSR);
	i2c_wait();

	I2C0_C1 |= I2C_C1_RSTA_MASK;

	I2C0_D = (ACCEL_I2C_ADDR << 1) | 0x01;

	 i2c_wait();

	 I2C0_C1 &= (~I2C_C1_TX_MASK);

	 I2C0_C1 |= I2C_C1_TXAK_MASK;

	 result = I2C0_D ;

	 i2c_stop();

	 result = I2C0_D ;

	 return result;
}


int main()
{

	i2c_init();
	i2c_Transmission(SLAVE_ADDR,MRSW);
	i2c_readregister(0xE0);

	return 0;
}







//	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
//	I2C0_F|= I2C_F_MULT(0);
//	I2C0_F|= 0x1C;
//	I2C0->C1 = 0;
//	I2C0_C1|= I2C_C1_IICEN_MASK;
//
//	I2C0_A1 |= I2C_ADDR;
//	I2C0_S |= I2C_S_SRW_MASK;
//
//	I2C0_C1|= I2C_C1_MST_MASK;
//	I2C0_C1 &= ~(I2C_C1_TX_MASK);
//	I2C0_C1 |= I2C_C1_RSTA_MASK;
//	I2C0_S|= I2C_S_IAAS_MASK;
//
//
//
//	I2C0_S |=I2C_S_BUSY_MASK;
//
//	//I2C0_C1 &= ~(I2C_C1_TXAK_MASK);
//	//I2C0_C1|= I2C_C1_IICIE_MASK;
//
//	I2C0_C2 &= ~(I2C_C2_ADEXT_MASK);




//int main()
//{
//
//	i2c_init();
//	uint8_t data;
//
//	data = I2C0_D;
//
//	return 0;
//}
//
//*/

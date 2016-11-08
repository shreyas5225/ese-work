#include <MKL25Z4.h>
#include "spi.h"

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */

void SysTick_Handler(void) {
  msTicks++;
}

/* Delay for argument number of systicks */
__inline static void delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}



int main (void) {

	volatile uint8_t c;
	volatile uint8_t rec[1];
	SystemInit();
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency */
	SysTick_Config(SystemCoreClock/1000);         /* Generate interrupt each 1 ms    */

	SPI_init();

	//while (!(SPI_status() & 0x20));
	//	SPI0->D = 0xFF;
	//while (!(SPI_status() & 0x80));
	  //	c = SPI0->D;
		//uint8_t data[2] = { 0x01, 0xFC };
	  uint8_t data[0] = {0xFF};
		//SPI_write(data, 2, 0x00);
	  SPI_write(data, 1);

	  SPI_write(rec, 1);

	  	return 0;
 }

/*
 * led.h
 *
 *  Created on: Dec 8, 2016
 *      Author: shva9978
 */
#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_
typedef enum
{
	OFF,
	RED,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
}LEDColour_t;
void LED_Init();
void LED_Control(uint8_t Character);
void LEDFunction(LEDColour_t LEDColour, uint16_t Brightness);
void LED_set(char value);


#endif /* SOURCES_LED_H_ */

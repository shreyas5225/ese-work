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
}Colour_LED;
void Initialize_LED();
void Change_LED(uint8_t Value);
void Change_Brightness(Colour_LED Colour, uint16_t Brightness);

#endif /* SOURCES_LED_H_ */

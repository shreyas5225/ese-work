/*
 * zero.h
 *
 *  Created on: Dec 6, 2016
 *      Author: shva9978
 */

#ifndef SOURCES_ZERO_H_
#define SOURCES_ZERO_H_

void reverse(char *str, int len);
void send_data(char character);
void print_string(char *ptr_str, uint32_t len);
void print_stringl(char *ptr);
int intToStr(int x, char str[], int d);
int power(int a, int n);
void ftoa(float n, char *res, int afterpoint);
uint16_t adc_temp(void);
void UART0_init(void);
void Calc_temp();
float Conv_temp (float b);


#endif /* SOURCES_ZERO_H_ */

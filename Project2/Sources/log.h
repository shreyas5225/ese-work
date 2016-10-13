/*
 * log.h
 *
 *  Created on: Oct 12, 2016
 *      Author: shva9978
 */

#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

void UART0_init(void);
void delaysMs(int n);

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
char ftoa(float n, char *res, int afterpoint);
void LOG_0(char * data, int len);
void LOG_1(char * data, float param,int point);

#endif /* SOURCES_LOG_H_ */

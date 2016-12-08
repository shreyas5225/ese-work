/*
 * rtc.h
 *
 *  Created on: Dec 6, 2016
 *      Author: shva9978
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

void rtc_clock();
void rtc_init();
//void alarm (int minutes, int seconds);
void RTC_isr_Seconds(void);
void RTC_Seconds_IRQHandler(void);
void RTC_IRQHandler(void);
void rtc_timer();
#endif /* SOURCES_RTC_H_ */

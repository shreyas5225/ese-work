/*
 * circular_buffer_test.h
 *
 *  Created on: Oct 12, 2016
 *      Author: shva9978
 */

#ifndef SOURCES_CIRCULAR_BUFFER_TEST_H_
#define SOURCES_CIRCULAR_BUFFER_TEST_H_

void initialize_test(void);
void buff_full_test(void);
void buff_empty_test(void);
void add_data_test(uint8_t itemtoadd);
void remove_data_test(void);
void initialize_buffer(cirbuf_t *cb1);
#endif /* SOURCES_CIRCULAR_BUFFER_TEST_H_ */

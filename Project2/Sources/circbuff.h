/*
 * circbuff.h
 *
 *  Created on: 13-Oct-2016
 *      Author: Shreyas
 */

#include <stdint.h>
#ifndef SOURCES_CIRCBUF_H_
#define SOURCES_CIRCBUF_H_
#define MAX_LEN 100

typedef enum{
	buffer_full,
	buffer_not_full,
	buffer_empty,
	buffer_not_empty,
	add_success,
	add_successwithwrap,
	read_success
	}state;

typedef struct
{
	uint8_t *data;
    uint8_t *buff;
    uint8_t *head;
    uint8_t *tail;
    uint32_t new_len;
    uint32_t length;
}cirbuf_t;
cirbuf_t tx_buf,rx_buf;
uint8_t *buff_ptr;
state full_buff(cirbuf_t *cb);
state empty_buff(cirbuf_t *cb);
state add_data_buff(cirbuf_t *cb, uint8_t item);
uint8_t read_data_buff(cirbuf_t *cb);
uint8_t* initialize(cirbuf_t *cb);
void destroy(cirbuf_t *cb);


#endif /* SOURCES_CIRCBUF_H_ */

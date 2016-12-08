/*
 * i2c.h
 *
 *  Created on: Dec 7, 2016
 *      Author: shva9978
 */

#ifndef SOURCES_I2C_H_
#define SOURCES_I2C_H_

void i2c_init();
void i2c_Transmission(unsigned char SlaveID,unsigned char Mode);

#define MWSR 0x00
#define MRSW 0x01
#define RH_READ      0xE5
#define TEMP_READ    0xE3
#define POST_RH_TEMP_READ 0xE0
#define USER1_READ        0xE7
#define ACCEL_I2C_ADDR   0x1C
#define SLAVE_ADDR  0x40
#define i2c_write_byte(data)   I2C0_D = data

#endif /* SOURCES_I2C_H_ */

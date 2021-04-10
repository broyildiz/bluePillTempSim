/*
 * IOL.h
 *
 *  Created on: 9 apr. 2021
 *      Author: Ömer
 */

#ifndef INC_IOL_H_
#define INC_IOL_H_

#include "main.h"


#define ADC_BUF_SIZE 512
#define ADC_RES 4096

uint16_t adc_buffer[ADC_BUF_SIZE];
int adc_cnt;

void IOL_set_res();
void IOL_i2c_scan();
void IOL_adc_get();


#endif /* INC_IOL_H_ */

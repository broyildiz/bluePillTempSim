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

#define R1 9910

void IOL_set_res();
void IOL_i2c_scan();
uint16_t IOL_adc_get();
void IOL_res_calc();
float remap(uint16_t i);


#endif /* INC_IOL_H_ */

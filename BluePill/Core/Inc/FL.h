/*
 * FL.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#ifndef INC_FL_H_
#define INC_FL_H_

#include "main.h"

#define NUM_ARGS_SET_RES	2

#define COMMAND_ERROR   	0
#define COMMAND_SET_RES 	1

#define MAX_ARGS 10

char *arg_buffer[MAX_ARGS];
int arg_cnt;

void FL_uart_decode();

#endif /* INC_FL_H_ */

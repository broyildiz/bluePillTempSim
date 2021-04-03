/*
 * FL.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#ifndef INC_FL_H_
#define INC_FL_H_

#include "main.h"


#define COMMAND_ERROR   	0
#define COMMAND_SET_RES 	1

#define SET_RES_ARGS		2
#define MAX_ARGS 			10
#define MAX_ARG_LEN			128
char *arg_buffer[MAX_ARGS];
int arg_cnt;
char single_arg[MAX_ARG_LEN];

typedef struct
{
	int digipot_no;
	int res;
}set_res_struct;

struct collection
{
	int cmd_no;
	set_res_struct set_res_cmd;
}command;

//void FL_init();
int FL_uart_decode();
int FL_get_cmd(char *str);
int FL_convert_args(int cmd_no, char **args);
//void FL_dereference(char **arg);

#endif /* INC_FL_H_ */

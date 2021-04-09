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
#define COMMAND_I2C_SCAN 	2

#define SET_RES_ARGS		2
#define I2C_SCAN_ARGS		0
#define MAX_ARGS 			10
#define MAX_ARG_LEN			128



/*
 * arg_buffer is essentially a 2D array.
 * It holds a pointer to a pointer to a string (from strtok() )
 * single_arg will hold one of these strings
 * The atoi function expects a char. If arg_buffer was used directly, this
 * would result in a warning: atoi makes pointer from integer without a cast
 * because arg_buffer is of the type char **
 * It would probably be smarter to use a 2D array, but this works for now
 */
char *arg_buffer[MAX_ARGS];
char single_arg[MAX_ARG_LEN];
int arg_cnt;

typedef struct
{
	int digipot_no;
	int res;
}set_res_struct;

typedef struct
{
	I2C_HandleTypeDef i2c_handle;
	uint16_t addr;
}i2_scan_struct;

struct collection
{
	int cmd_no;
	i2_scan_struct i2c_scan_cmd;
	set_res_struct set_res_cmd;
}command;

//void FL_init();
int FL_uart_decode();
int FL_get_cmd(char *str);
int FL_convert_args(int cmd_no, char **args);

void FL_error_handler(char *file_name, char *function_name, char *msg);
void FL_debug(char *s);

#endif /* INC_FL_H_ */

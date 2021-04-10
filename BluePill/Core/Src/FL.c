/*
 * FL.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#include "FL.h"

void FL_clean(I2C_HandleTypeDef hi2c2, ADC_HandleTypeDef hadc1)
{
	int i;
	memset(&command, 0, sizeof(command));
	command.i2c_scan_cmd.i2c_handle = hi2c2;
	command.adc_get_cmd.adc_handle = hadc1;
	for(i = 0; i < LINE_BUFLEN; i++)
		input.line_rx_buffer[i] = 0;

}

int FL_uart_decode()
{
	FL_debug("Entered FL_uart_decode function");

	char delim[2] = ","; 	// This string will be used to parse the main input string
	char *token;			// This pointer will hold current parsed string
	memset(arg_buffer, '\0', sizeof(arg_buffer));
	memset(single_arg, '\0',  sizeof(single_arg));
	arg_cnt = 0;

	/*
	 * sources for parsing the string
	 * source 1, using strtok:
	 * https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
	 * source 2, storing the token:
	 * https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
	 */

	/* get the first token */
	token = strtok(input.line_rx_buffer, delim);

	/* walk through other tokens */
	while( token != NULL ) {
		printf( " %s\n", token );
		arg_buffer[arg_cnt++] = token; // Store the token for later use
		token = strtok(NULL, delim);
	}

	// Some debugging
	int i;
	if(debug_enable)
	{
		for(i = 0; i < arg_cnt; i++)
		{
			printf("Arg buffer [%d] = %s\n", i, arg_buffer[i]);
		}
	}

	// The first argument is the name of the command
	// Determine which command is sent
	command.cmd_no = FL_get_cmd(arg_buffer[0]);

	if(command.cmd_no == COMMAND_ERROR)
	{
		FL_error_handler("FL.c", "FL_uart_decode","Unsupported Command");
		return -1;
	}

	/*
	 * Preparation for argument conversion
	 * Each command has its own arguments and should be parsed accordingly
	 */
	arg_cnt--; 	// The first argument is the command name, compensate for it

	switch(command.cmd_no)
	{
		case COMMAND_SET_RES:
		{
			if(arg_cnt != SET_RES_ARGS)
			{
				FL_error_handler("FL.c", "FL_uart_decode","Wrong number of arguments arguments\n");
				printf("Expected %d arguments, got %d arguments\n", SET_RES_ARGS, arg_cnt);
			}
			else
			{
				FL_convert_args(command.cmd_no, arg_buffer);
			}
		}break;
		case COMMAND_I2C_SCAN:
		{
			// No arguments to gather
		}break;
		case COMMAND_ADC_GET:
		{
			// No arguments to gather
		}break;
		default:
		{
			FL_debug("Don't know about this default case1");
		}
	}
	FL_debug("Exiting FL_uart_decode function");
	return 0;
}

/*
 *  This function takes the first argument passed to the FL and tries to
 *  determine which command is sent
 */
int FL_get_cmd(char *str)
{
	FL_debug("Entered FL_get_cmd function");

	char set_res[] = "set_res";
	char i2c_scan[] = "i2c_scan";
	char adc_get[] = "adc_get";
	int ret = COMMAND_ERROR;

	if(strcmp(str, set_res) == 0)
	{
		FL_debug("command = set_res");
		ret = COMMAND_SET_RES;
	}

	if(strcmp(str, i2c_scan) == 0)
	{
		FL_debug("command = set_res");
		ret = COMMAND_I2C_SCAN;
	}
	if(strcmp(str, adc_get) == 0)
	{
		FL_debug("command = set_res");
		ret = COMMAND_ADC_GET;
	}
//		else
//		{
//			FL_debug("command = unrecognized");
//			ret = COMMAND_ERROR;
//		}

	FL_debug("Exiting FL_get_cmd function");
	return ret;
}

int FL_convert_args(int cmd_no, char **args)
{
	FL_debug("Entered FL_convert_args function");
	switch(cmd_no)
	{
		case COMMAND_SET_RES:
		{
			// Copy a string from args into single_arg.
			// See FL.h for more details
			strcpy(single_arg, args[1]);
			if(debug_enable)
				printf("Single arg = %s\n", single_arg);
			command.set_res_cmd.digipot_no = atoi(single_arg);

			strcpy(single_arg, args[2]);
			if(debug_enable)
				printf("Single arg = %s\n", single_arg);
			command.set_res_cmd.res = atoi(single_arg);

		}break;
		default:
		{
			FL_debug("Don't know about this default case2");
		}
	}

	return 0;
	FL_debug("Exiting FL_convert_args function");
}


void FL_error_handler(char *file_name, char *function_name, char *msg)
{
	printf("ERROR in %s\t%s\n", file_name, function_name);
	printf("message:\t%s\n", msg);
}

void FL_debug(char *s)
{
	if(debug_enable)
	{
		printf("%s\n",s);
	}
}

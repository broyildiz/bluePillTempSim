/*
 * FL.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#include "FL.h"

int FL_uart_decode()
{
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
	for(i = 0; i < arg_cnt; i++)
	{
		printf("Arg buffer [%d] = %s \n", i, arg_buffer[i]);
	}

	// The first argument is the name of the command
	// Determine which command is sent
	command.cmd_no = FL_get_cmd(arg_buffer[0]);

	if(command.cmd_no == COMMAND_ERROR)
	{
		printf("Command error\n");
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
				printf("ERROR: Wrong number of arguments arguments\n");
				printf("Expected %d arguments, got %d arguments\n", SET_RES_ARGS, arg_cnt);
			}
			else
			{
				FL_convert_args(command.cmd_no, arg_buffer);
			}
		}break;
		default:
		{
			printf("Don't know\n");
		}
	}
	return 0;
}

/*
 *  This function takes the first argument passed to the FL and tries to
 *  determine which command is sent
 */
int FL_get_cmd(char *str)
{
	char set_res[] = "set_res";
	int ret;

	if(strcmp(str, set_res) == 0)
	{
		printf("command = set_res\n");
		ret = COMMAND_SET_RES;
	}
	else
	{
		printf("command = unrecognized\n");
		ret = COMMAND_ERROR;
	}

	return ret;
}

int FL_convert_args(int cmd_no, char **args)
{

	switch(cmd_no)
	{
		case COMMAND_SET_RES:
		{
			// Copy a string from args into single_arg.
			// See FL.h for more details
			strcpy(single_arg, args[1]);
			printf("Single arg = %s\n", single_arg);
			command.set_res_cmd.digipot_no = atoi(single_arg);

			strcpy(single_arg, args[2]);
			printf("Single arg = %s\n", single_arg);
			command.set_res_cmd.res = atoi(single_arg);

		}break;
		default:
		{
			printf("Don't know 2\n");
		}
	}


	return 0;
}

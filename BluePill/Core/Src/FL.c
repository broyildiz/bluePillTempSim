/*
 * FL.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#include "FL.h"

//void FL_init()
//{
//	memset(command, 0, sizeof(command));
//}

int FL_uart_decode()
{
	char delim[2] = ","; 	// This string will be used to parse the main input string
	char *token;			// This pointer will hold current parsed string
	memset(arg_buffer, '\0', sizeof(arg_buffer));
	memset(single_arg, '\0',  sizeof(single_arg));
	arg_cnt = 0;

	/* get the first token */
	token = strtok(input.line_rx_buffer, delim);

	/* walk through other tokens */
	while( token != NULL ) {
		printf( " %s\n", token );
		arg_buffer[arg_cnt++] = token;
		token = strtok(NULL, delim);
	}

	int i;
	for(i = 0; i < arg_cnt; i++)
	{
		printf("Arg buffer [%d] = %s\n", i, arg_buffer[i]);
	}
	command.cmd_no = FL_get_cmd(arg_buffer[0]);

	if(command.cmd_no == COMMAND_ERROR)
	{
		printf("Command error\n");
		return -1;
	}

	switch(command.cmd_no)
	{
		case COMMAND_SET_RES:
		{
			if(arg_cnt-1 != SET_RES_ARGS)
			{
				printf("ERROR: Wrong number of arguments arguments\n");
				printf("Expected %d arguments, got %d arguments\n", SET_RES_ARGS, arg_cnt);
				break;
			}
			FL_convert_args(command.cmd_no, arg_buffer);

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
//	int i;
	switch(cmd_no)
	{
		case COMMAND_SET_RES:
		{
				strcpy(single_arg, args[1]);
				printf("Single arg = %s\n", single_arg);
				command.set_res_cmd.digipot_no = atoi(single_arg);
				strcpy(single_arg, args[2]);
				printf("Single arg = %s\n", single_arg);
				command.set_res_cmd.res = atoi(single_arg);

//			command.set_res_cmd.digipot_no = atoi((char)args[1]);
//			command.set_res_cmd.digipot_no = atoi(args[2]);
		}break;
		default:
		{
			printf("Don't know 2\n");
		}
	}


	return 0;
}

//void FL_dereference(char **arg)
//{
//	strcpy(single_arg, arg);
//}

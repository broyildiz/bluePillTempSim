/*
 * FL.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#include "FL.h"

void FL_uart_decode()
{
	char delim[2] = ","; 	// This string will be used to parse the main input string
	char *token;			// This pointer will hold current parsed string
	memset(arg_buffer, '\0', sizeof(arg_buffer));
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


}


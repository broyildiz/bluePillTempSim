/*
 * LL.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Ömer
 */

#include "LL.h"

int LL_exec()
{
	switch(command.cmd_no)
	{
	case COMMAND_SET_RES:
	{
		printf("Executed COMMAND_SET_RES\n");
	}break;
	default:
	{
		printf("Dunno 3\n");
	}
	}
	return 0;
}


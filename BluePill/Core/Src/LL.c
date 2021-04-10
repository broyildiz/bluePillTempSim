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
		IOL_set_res();
		printf("Executed COMMAND_SET_RES\n");
	}break;
	case COMMAND_I2C_SCAN:
	{
		IOL_i2c_scan();
		printf("Executed COMMAND_SET_RES\n");
	}break;
	case COMMAND_ADC_GET:
	{
		IOL_adc_get();
	}break;
	case COMMAND_RES_CALC:
	{
		IOL_res_calc();
	}break;
	default:
	{
		printf("Dunno 3\n");
	}
	}
	return 0;
}


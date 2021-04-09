/*
 * IOL.c
 *
 *  Created on: 9 apr. 2021
 *      Author: Ömer
 */

#include "IOL.h"

void IOL_set_res()
{
	uint8_t wiper = 0x00;

	switch(command.set_res_cmd.digipot_no) /* According to the datasheet, the following values are the memory addresses of the individual subdigipots */
	{
		case 0: wiper = 0x00; break;
		case 1: wiper = 0x01; break;
		case 2: wiper = 0x06; break;
		case 3: wiper = 0x07; break;
		default:
		{
			FL_error_handler("IOL.c", "IOL_set_res", "Unsupported digipot number");
			wiper = 0x10;
		}break;
	}

	uint16_t addr = 0x2c << 1;
	uint8_t tx[] = { wiper << 4, (uint8_t)command.set_res_cmd.res};
	uint16_t num = 2;
	HAL_I2C_Master_Transmit(&command.i2c_scan_cmd.i2c_handle, addr, tx, num, HAL_MAX_DELAY );

}



void IOL_i2c_scan()
{
	printf("Scanning I2C bus:\r\n");
	HAL_StatusTypeDef result;
	uint8_t i;
	for (i=1; i<128; i++)
	{
	  /*
	   * the HAL wants a left aligned i2c address
	   * &hi2c1 is the handle
	   * (uint16_t)(i<<1) is the i2c address left aligned
	   * retries 2
	   * timeout 2
	   */
	  result = HAL_I2C_IsDeviceReady(&command.i2c_scan_cmd.i2c_handle, (uint16_t)(i<<1), 2, 2);
	  if (result != HAL_OK) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
	  {
		  printf("."); // No ACK received at that address
	  }
	  if (result == HAL_OK)
	  {
		  printf("0x%X", i); // Received an ACK at that address
		  command.i2c_scan_cmd.addr = i;
	  }
	}
	printf("\r\n");
}

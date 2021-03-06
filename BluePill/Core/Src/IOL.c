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

uint16_t IOL_adc_get()
{
	HAL_ADC_Start(&command.adc_get_cmd.adc_handle);
	HAL_ADC_PollForConversion(&command.adc_get_cmd.adc_handle, HAL_MAX_DELAY);
	uint16_t ret = HAL_ADC_GetValue(&command.adc_get_cmd.adc_handle);
	printf("\nADC Value = %d\n\n", (int)ret);
	return ret;
}

void IOL_res_calc()
{
//	printf("Entering Res Calc Function\n");
	uint16_t adc = IOL_adc_get();
	float voltage = remap(adc);
	printf("ADC to voltage: %f\n", voltage);
	if(voltage)
	{
		float R2 = R1 * ( 1 / ((3.3 / voltage) - 1));
		printf("Resistance = %f\n", R2);
	}
	else
	{
		printf("Resistance = 0\n");
	}

}


float remap(uint16_t i)
{
  float input_start = 0;
  float input_end = ADC_RES-1;
  float output_start = 0.0;
  float output_end = 3.3;
  float slope = 0.0;

  float output = 0;

  slope = (output_end - output_start) / (input_end - input_start);
  output = (output_start + slope * (i -input_start));

  return output;
}

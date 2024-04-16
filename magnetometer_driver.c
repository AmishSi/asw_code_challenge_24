#include "i2c.h"
#include "magnetometer_driver.h"

#include <stdint.h>
#include <stdio.h>

uint8_t i2c_get_full_scale_config(
	void)
{
	uint8_t bus;
	uint8_t* reg_val;
	uint8_t fs_bit_val;
	static uint8_t gauss;

	bus = (SAD << 1) & 0x00; // for write

	if(STATUS_OK == i2c_read(SAD, CTRL_REG2, 1, reg_val))
	{
	fs_bit_val= (01100000b & reg_val) >> 5;
	switch(fs_bit_val)
	{
		case 0x00 :
			gauss = 0x04;	
			break;

		case 0x01 :
			gauss = 0x08;	
			break;

		case 0x10 :
			gauss = 0x12;	
			break;

		case 0x11 :
			gauss = 0x16;	
			break;

		default :
			break;	
	}
	}

	return gauss;
}

float i2c_get_output_data_rate(
	void)
{
	uint8_t* reg_val;
	uint8_t do_bits_val;
	static float out_data_rate;

	if(STATUS_OK == i2c_read(SAD, CTRL_REG1, 1, reg_val))
	{
	do_bits_val= 00011100b & reg_val;
	switch(do_bits_val)
	{
		case 00000000b :
			out_data_rate = 0.625;	
			break;

		case 00000100b :
			out_data_rate = 1.25;
			break;	

		case 00001000b :
			out_data_rate = 2.5;
			break;	

		case 00001100b :
			out_data_rate = 5.00;	
			break;

		case 00010000b :
			out_data_rate = 10.00;	
			break;

		case 00010100b :
			out_data_rate = 20.00;	
			break;

		case 00011000b :
			out_data_rate = 40.00;	
			break;

		case 00011100b :
			out_data_rate = 80.00;
			break;

		default :
			break;	
	}
	}

	return out_data_rate;
}

status_t i2c_set_output_data_rate(
	float value)
{
	status_t status = STATUS_ERROR;
	uint8_t* reg_val;

	if(0.625f == value)
	{
		*reg_val = 00000000b;
	}
	else if(1.25f == value)
	{
		*reg_val = 00000100b;
	}
	else if(2.5f == value)
	{
		*reg_val = 00001000b;
	}
	else if(5.00f == value)
	{
		*reg_val = 00001100b;
	}
	else if(10.00f == value)
	{
		*reg_val = 00010000b;
	}
	else if(20.00f == value)
	{
		*reg_val = 00010100b;
	}
	else if(40.00f == value)
	{
		*reg_val = 00011000b;
	}
	else if(80.00f == value)
	{
		*reg_val = 00011100b;
	}
	else
	{
		//do nothing
	}
		
	if(STATUS_OK == i2c_write(SAD, CTRL_REG1, 1, reg_val))
	{
		status = STATUS_OK;
	}

	return status;
}

/***********************************
*API to enable the interrupt
************************************/
status_t enable_interrupt(
	void)
{
	status_t status = STATUS_ERROR;
	uint8_t* reg_val;

	*reg_val = 11101111b;
	
	if(STATUS_OK == i2c_write(SAD, INT_CFG, 1, reg_val))
	{
		status = STATUS_OK;
	}

	return status;
}

/***********************************
*API to disable the interrupt
************************************/
status_t disable_interrupt(
	void)
{
	status_t status = STATUS_ERROR;
	uint8_t* reg_val;

	*reg_val = 00001000b;
	
	if(STATUS_OK == i2c_write(SAD, INT_CFG, 1, reg_val))
	{
		status = STATUS_OK;
	}

	return status;
}

/***********************************
*Output data status register STATUS_REG (27h) has to be checked before calling this API
*
*Input parameter axis has to be given X_AXIS, Y_AXIS, Z_AXIS for a particular axis
************************************/
status_t read_output_data_axis(
	int16_t* output_data, uint8_t axis)
{
	status_t status = STATUS_ERROR;
	uint8_t* reg_val_l;
	uint8_t* reg_val_h;

	if(X_AXIS == axis)
	{
		if(STATUS_OK == i2c_read(SAD, OUT_X_L , 1, reg_val_l))
		{
			if(STATUS_OK == i2c_read(SAD, OUT_X_H , 1, reg_val_2))
			{
				*output_data = ( (((int16_t)*reg_val_h) << 8u) | (int16_t)*reg_val_l);
			}
			status STATUS_OK;
		}
	}
	else if(Y_AXIS == axis)
	{
		if(STATUS_OK == i2c_read(SAD, OUT_Y_L , 1, reg_val_l))
		{
			if(STATUS_OK == i2c_read(SAD, OUT_Y_H , 1, reg_val_2))
			{
				*output_data = ( (((int16_t)*reg_val_h) << 8u) | (int16_t)*reg_val_l);
			}
			status STATUS_OK;
		}
	}
	else if(Z_AXIS == axis)
	{
		if(STATUS_OK == i2c_read(SAD, OUT_Z_L , 1, reg_val_l))
		{
			if(STATUS_OK == i2c_read(SAD, OUT_Z_H , 1, reg_val_2))
			{
				*output_data = ( (((int16_t)*reg_val_h) << 8u) | (int16_t)*reg_val_l);
			}
			status STATUS_OK;
		}
	}
	else
	{
		//do nothing
	}

	return status;
}

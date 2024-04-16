#ifndef MAGNETOMETER_DRIVER_HEADER_H
#define MAGNETOMETER_DRIVER_HEADER_H

//Need to add all the registers whichever are required further
#define CTRL_REG1 0x20h
#define CTRL_REG2 0x21h
#define OUT_X_L 0x28h
#define OUT_X_H 0x29h
#define OUT_Y_L 0x2Ah
#define OUT_Y_H 0x2Bh
#define OUT_Z_L 0x2Ch
#define OUT_Z_H 0x2Dh
#define INT_CFG 0x30h

#define X_AXIS 0x00h
#define Y_AXIS 0x01h
#define Z_AXIS 0x02h

/*********************
#define SDO/SA1_PIN_HIGH 0x01 if pin is connected to VDD
#define SDO/SA1_PIN_LOW if pin is connected to ground
Considering SDO/SA1_PIN is connected to VDD here below definition is done
*********************/

#define SDO/SA1_PIN_HIGH

#ifdef SDO/SA1_PIN_HIGH 
#define SAD 0011110b
#else 
#define SAD 0011100b
#endif

uint8_t i2c_get_full_scale_config(
	void);

float i2c_get_output_data_rate(
	void);

status_t i2c_set_output_data_rate(
	float value);

status_t enable_interrupt(
	void);

status_t disable_interrupt(
	void);

status_t read_output_data_axis(
	uint16_t* output_data, uint8_t axis);

#endif

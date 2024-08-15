#pragma once
#include "stm32l4xx_hal.h"
#include "i2c.h"

unsigned int I2CHelper_ReadRegisterAsInt(I2C_HandleTypeDef *i2c, unsigned char device, unsigned char address);
unsigned short I2CHelper_ReadRegisterAsShort(I2C_HandleTypeDef *i2c, unsigned char device, unsigned char address);
unsigned char I2CHelper_ReadRegisterAsChar(I2C_HandleTypeDef *i2c, unsigned char device, unsigned char address);

void I2CHelper_ReadRegister(I2C_HandleTypeDef *i2c, unsigned char device, unsigned char address, unsigned char *receive_buffer, unsigned char size);
void I2CHelper_WriteRegister(I2C_HandleTypeDef *i2c, unsigned char device, unsigned char address, unsigned short value);

unsigned char I2CHelper_GetFirstAddress(I2C_HandleTypeDef *i2c);

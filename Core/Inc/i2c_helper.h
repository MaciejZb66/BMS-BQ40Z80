#pragma once
#include "stm32l4xx_hal.h"
#include "i2c.h"

uint32_t I2CHelper_ReadRegisterAsInt(I2C_HandleTypeDef *i2c, uint8_t device, uint8_t address);//32bit
uint16_t I2CHelper_ReadRegisterAsShort(I2C_HandleTypeDef *i2c, uint8_t device, uint8_t address);//16bit
uint8_t I2CHelper_ReadRegisterAsChar(I2C_HandleTypeDef *i2c, uint8_t device, uint8_t address);//8bit

void I2CHelper_ReadRegister(I2C_HandleTypeDef *i2c, uint8_t device, uint8_t address, uint8_t *receive_buffer, uint8_t size);
void I2CHelper_WriteRegister(I2C_HandleTypeDef *i2c, uint8_t device, uint8_t address, uint16_t value);

uint8_t I2CHelper_GetFirstAddress(I2C_HandleTypeDef *i2c);

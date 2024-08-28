#pragma once
#include "stm32l4xx_hal.h"
#include "i2c.h"

typedef enum{
	CONNECTED,
	CHANGED_ADDRESS,
	INVALID_DEVICE
}CONNECTION_STATUS;

uint32_t I2CHelper_ReadRegisterAsInt(BQ_data* BMS, uint8_t address);//32bit
uint16_t I2CHelper_ReadRegisterAsShort(BQ_data* BMS, uint8_t address);//16bit
uint8_t I2CHelper_ReadRegisterAsChar(BQ_data* BMS, uint8_t address);//8bit

void I2CHelper_ReadRegister(BQ_data* BMS, uint8_t address, uint8_t *receive_buffer, uint8_t size);
void I2CHelper_WriteRegister(BQ_data* BMS, uint8_t address, uint16_t value);

CONNECTION_STATUS I2CHelper_CheckAddress(BQ_data* BMS);

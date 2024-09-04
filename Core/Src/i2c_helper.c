#include "i2c_helper.h"

/**
 * @brief reading from i2c address 4 bytes
 * @param i2c I2C_HandleTypeDef pointer
 * @param device device address
 * @param address address from read
 **/
uint32_t I2CHelper_ReadRegisterAsInt(BQ_data* BMS, uint8_t address)
{
	uint8_t buf[4];
	I2CHelper_ReadRegister(BMS, address, buf, 4);

	uint32_t result = 0;

	result = result | (buf[0]);
	result = result | (buf[1] << 8);
	result = result | (buf[2] << 16);
	result = result | (buf[3] << 24);

	return result;
}

/**
 * @brief reading from i2c address 2 bytes
 * @param i2c I2C_HandleTypeDef pointer
 * @param device device address
 * @param address address from read
 **/
uint16_t I2CHelper_ReadRegisterAsShort(BQ_data* BMS, uint8_t address)
{
	uint8_t buf[2];
	I2CHelper_ReadRegister(BMS, address, buf, 2);
	uint16_t result = 0;

	result = result | buf[0];
	result = result | (buf[1] << 8);

	return result;
}

/**
 * @brief reading from i2c address 1 byte
 * @param i2c I2C_HandleTypeDef pointer
 * @param device device address
 * @param address address from read
 **/
uint8_t I2CHelper_ReadRegisterAsChar(BQ_data* BMS, uint8_t address)
{
	uint8_t buf[1];
	I2CHelper_ReadRegister(BMS, address, buf, 1);

	return buf[0];
}

/**
 * @brief read data from register of device
 * @param address where to read
 * @param receive_buffer array to write
 * @param size receive_buffer size
 */
void I2CHelper_ReadRegister(BQ_data* BMS, uint8_t address, uint8_t *receive_buffer, uint8_t size)
{
	HAL_I2C_Master_Transmit(BMS->bq_i2c, BMS->bq_deviceAddress, &address, 1, 100);
	HAL_I2C_Master_Receive(BMS->bq_i2c, BMS->bq_deviceAddress,  receive_buffer, size, 100);
}

/**
 * @brief write data to register of device
 * @param address: where to write
 * @param value: data to write 
 */
void I2CHelper_WriteRegister(BQ_data* BMS, uint8_t address, uint16_t value)
{
	uint8_t data[3];

	data[0] = address;
	data[1] = value >> 8;
	data[2] = value;

	HAL_I2C_Master_Transmit(BMS->bq_i2c, BMS->bq_deviceAddress, data, 3, 100); // data is the start pointer of our array
}

/**
 * @brief scanning i2c devices and return first
 * @param i2c I2C_HandleTypeDef pointer
 * @return first i2c device
 */
void I2CHelper_CheckAddress(BQ_data* BMS)
{
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(BMS->bq_i2c, BMS->bq_deviceAddress, 3, 5);
	if (ret == HAL_BUSY){
		BMS->connection = NEED_RESET;
		return;
	}
	if (ret == HAL_OK)
	{
		BMS->connection = CONNECTED;
		return;
	}
	for (uint8_t i = 1; i < 255; i++)
	{
		ret = HAL_I2C_IsDeviceReady(BMS->bq_i2c, i, 3, 5);
		if (ret == HAL_OK)
		{
			BMS->bq_deviceAddress = i;
			BMS->connection = CHANGED_ADDRESS;
			return;
		}
		HAL_Delay(1);
	}
	BMS->connection = INVALID_DEVICE;
}

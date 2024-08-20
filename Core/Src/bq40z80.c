#include "bq40z80.h"

uint8_t bq_deviceAddress = 0x0B;

//BQ_data BMS = NULL;
//uint8_t number_of_inited = 0;
extern BQ_data BMS_1;
/**
 * @brief bq40z80 initialization
 * @param i2c i2c pointer
 */
void BQ_Init(I2C_HandleTypeDef *i2c)
{
    BMS_1.bq_i2c = i2c;
    if(i2c == &hi2c1){
    	__HAL_RCC_I2C1_CLK_ENABLE();
    }
#ifdef three_bms
    if(i2c == &hi2c2){
		__HAL_RCC_I2C2_CLK_ENABLE();
	}
    if(i2c == &hi2c3){
		__HAL_RCC_I2C3_CLK_ENABLE();
	}
#endif

//    ("[BQ] Started", 12);
//    if (USE_SCANNER == 1)
//    {
#ifdef USE_SCANNER
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(i2c, bq_deviceAddress << 1, 3, 100);
	while (ret != HAL_OK)
	{
//            ("[BQ] device not founded", 23);
		ret = HAL_I2C_IsDeviceReady(i2c, bq_deviceAddress << 1, 3, 100);
		HAL_Delay(1000);
	#ifdef debug
		if(ret == HAL_ERROR){
			__asm("nop");
		}
	#endif
	}
#endif
//    }

    

    HAL_Delay(1500);
    BQAction_UpdateData(BMS_1);
    BQAction_TryUnsealedDevice(BMS_1);

    BQAction_SetManufacturingAllFet(BMS_1, false);
    BQAction_SetManufacturingFuse(BMS_1, false);
    BQAction_SetCalibration(BMS_1, false);
    BQAction_SetManufacturingGauging(BMS_1, true);
    BQAction_SetManufacturingPF(BMS_1, true);
    BQAction_SetManufacturingLF(BMS_1, true);
    BQAction_SetLed(BMS_1, false);

    BQAction_UpdateData(BMS_1);

    //BQ_ForceUpdateFlash();

    //BQ_BoundaryCellVoltage voltages = BQ_GetBoundaryCellVoltage();

//    ("[BQ] initialized", 16);
}

/**
 * @brief write data to flash
 * @param addr flash register
 * @param writeData short value to flash
 */
void BQ_WriteFlash(BQ_data BMS, uint16_t addr, uint16_t writeData)
{
    uint8_t data[6];
    data[0] = 0x44;
    data[1] = 0x04;
    data[2] = addr & 0xff;
    data[3] = (addr >> 8) & 0xff;
    data[4] = writeData & 0xff;
    data[5] = (writeData >> 8) & 0xff;

    HAL_I2C_Master_Transmit(BMS.bq_i2c, bq_deviceAddress << 1, data, 6, 100);
}

/**
 * @brief write byte to flash
 * @param addr flash register
 * @param writeData char value to flash
 */
void BQ_WriteFlashByte(BQ_data BMS, uint16_t addr, uint8_t writeData)
{
    uint8_t data[5];
    data[0] = 0x44;
    data[1] = 0x03;
    data[2] = addr & 0xff;
    data[3] = (addr >> 8) & 0xff;
    data[4] = writeData;

    HAL_I2C_Master_Transmit(BMS.bq_i2c, bq_deviceAddress << 1, data, 5, 100);
}

/**
 * @brief send command to ManufacturerBlockAccess()
 * @param command command to send
 */
void BQ_WriteMABlockCommand(BQ_data BMS, uint16_t command)
{
    // send 0x44, then count of bytes, then command
    uint8_t buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(BMS.bq_i2c, bq_deviceAddress << 1, buf, 4, 100);
}

/**
 * @brief reading from ManufacturerBlockAccess()
 * @param command command from read
 * @param receive array to receive
 * @param size array size
 */
void BQ_ReadMABlockCommand(BQ_data BMS, uint16_t command, uint8_t *receive, uint8_t size)
{
    // send 0x44, then count of bytes, then command
    uint8_t buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(BMS.bq_i2c, bq_deviceAddress << 1, buf, 4, 100);

    // send 0x44, then receive size
    uint8_t addr[2] = {0x44, 2 + size};
    HAL_I2C_Master_Transmit(BMS.bq_i2c, bq_deviceAddress << 1, addr, 2, 100);

    uint8_t result[35] = {0};
    HAL_I2C_Master_Receive(BMS.bq_i2c, bq_deviceAddress << 1, result, 35, 100);

    for (int i = 0; i < size; i++)
    {
        receive[i] = result[i + 3];
    }
}

/**
 * @brief reading from ManufacturerBlockAccess() as uint16_t
 * @param command command to read
 * @return 16bit value from command
 */
uint16_t BQ_ReadCommandAsShort(BQ_data BMS, uint16_t command)
{
    uint8_t buf[2];

    BQ_ReadMABlockCommand(BMS, command, buf, 2);

    uint16_t result = 0;

    result = result | buf[0];
    result = result | (buf[1] << 8);

    return result;
}

/**
 * @brief reading from ManufacturerBlockAccess() as uint16_t
 * @param command command to read
 * @return 16bit value from command
 */
uint8_t BQ_ReadCommandAsChar(BQ_data BMS, uint16_t command)
{
    uint8_t buf[1];

    BQ_ReadMABlockCommand(BMS, command, buf, 1);

    return buf[0];
}

/**
 * @brief reading from ManufacturerBlockAccess() as uint32_t
 * @param command command to read
 * @return 32bit value from command
 */
uint32_t BQ_ReadCommandAsInt(BQ_data BMS, uint16_t command)
{
    uint8_t buf[4];

    BQ_ReadMABlockCommand(BMS, command, buf, 4);

    uint32_t result = 0;

    result = result | (buf[0]);
    result = result | (buf[1] << 8);
    result = result | (buf[2] << 16);
    result = result | (buf[3] << 24);

    return result;
}

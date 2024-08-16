#include "bq40z80.h"

uint8_t bq_deviceAddress = 0x0B;
//I2C_HandleTypeDef *bq_i2c = NULL;
//uint8_t number_of_inited = 0;

/**
 * @brief bq40z80 initialization
 * @param i2c i2c pointer
 */
void BQ_Init(I2C_HandleTypeDef *i2c)
{
//    bq_i2c = i2c;
    if(i2c == &hi2c1){
    	__HAL_RCC_I2C1_CLK_ENABLE();
    }
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
        }
#endif
//    }

    

    HAL_Delay(1500);
    BQAction_UpdateData(i2c);
    BQAction_TryUnsealedDevice(i2c);

    BQAction_SetManufacturingAllFet(i2c, false);
    BQAction_SetManufacturingFuse(i2c, false);
    BQAction_SetCalibration(i2c, false);
    BQAction_SetManufacturingGauging(i2c, true);
    BQAction_SetManufacturingPF(i2c, true);
    BQAction_SetManufacturingLF(i2c, true);
    BQAction_SetLed(i2c, false);

    BQAction_UpdateData(i2c);

    //BQ_ForceUpdateFlash();

    //BQ_BoundaryCellVoltage voltages = BQ_GetBoundaryCellVoltage();

//    ("[BQ] initialized", 16);
}

/**
 * @brief write data to flash
 * @param addr flash register
 * @param writeData short value to flash
 */
void BQ_WriteFlash(I2C_HandleTypeDef *bq_i2c, uint16_t addr, uint16_t writeData)
{
    uint8_t data[6];
    data[0] = 0x44;
    data[1] = 0x04;
    data[2] = addr & 0xff;
    data[3] = (addr >> 8) & 0xff;
    data[4] = writeData & 0xff;
    data[5] = (writeData >> 8) & 0xff;

    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, data, 6, 100);
}

/**
 * @brief write byte to flash
 * @param addr flash register
 * @param writeData char value to flash
 */
void BQ_WriteFlashByte(I2C_HandleTypeDef *bq_i2c, uint16_t addr, uint8_t writeData)
{
    uint8_t data[5];
    data[0] = 0x44;
    data[1] = 0x03;
    data[2] = addr & 0xff;
    data[3] = (addr >> 8) & 0xff;
    data[4] = writeData;

    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, data, 5, 100);
}

/**
 * @brief send command to ManufacturerBlockAccess()
 * @param command command to send
 */
void BQ_WriteMABlockCommand(I2C_HandleTypeDef *bq_i2c, uint16_t command)
{
    // send 0x44, then count of bytes, then command
    uint8_t buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, buf, 4, 100);
}

/**
 * @brief reading from ManufacturerBlockAccess()
 * @param command command from read
 * @param receive array to receive
 * @param size array size
 */
void BQ_ReadMABlockCommand(I2C_HandleTypeDef *bq_i2c, uint16_t command, uint8_t *receive, uint8_t size)
{
    // send 0x44, then count of bytes, then command
    uint8_t buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, buf, 4, 100);

    // send 0x44, then receive size
    uint8_t addr[2] = {0x44, 2 + size};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, addr, 2, 100);

    uint8_t result[35] = {0};
    HAL_I2C_Master_Receive(bq_i2c, bq_deviceAddress << 1, result, 35, 100);

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
uint16_t BQ_ReadCommandAsShort(I2C_HandleTypeDef *bq_i2c, uint16_t command)
{
    uint8_t buf[2];

    BQ_ReadMABlockCommand(bq_i2c, command, buf, 2);

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
uint8_t BQ_ReadCommandAsChar(I2C_HandleTypeDef *bq_i2c, uint16_t command)
{
    uint8_t buf[1];

    BQ_ReadMABlockCommand(bq_i2c, command, buf, 1);

    return buf[0];
}

/**
 * @brief reading from ManufacturerBlockAccess() as uint32_t
 * @param command command to read
 * @return 32bit value from command
 */
uint32_t BQ_ReadCommandAsInt(I2C_HandleTypeDef *bq_i2c, uint16_t command)
{
    uint8_t buf[4];

    BQ_ReadMABlockCommand(bq_i2c, command, buf, 4);

    uint32_t result = 0;

    result = result | (buf[0]);
    result = result | (buf[1] << 8);
    result = result | (buf[2] << 16);
    result = result | (buf[3] << 24);

    return result;
}

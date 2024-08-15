#include "bq40z80.h"

unsigned char bq_deviceAddress = 0x0B;
I2C_HandleTypeDef *bq_i2c = NULL;

/**
 * @brief bq40z80 initialization
 * @param i2c i2c pointer
 */
void BQ_Init(I2C_HandleTypeDef *i2c)
{
    bq_i2c = i2c;
    if(bq_i2c == &hi2c1){
    	__HAL_RCC_I2C1_CLK_ENABLE();
    }
//    ("[BQ] Started", 12);
//    if (USE_SCANNER == 1)
//    {
#ifdef USE_SCANNER
        HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(bq_i2c, bq_deviceAddress << 1, 3, 100);
        while (ret != HAL_OK)
        {
//            ("[BQ] device not founded", 23);
            ret = HAL_I2C_IsDeviceReady(bq_i2c, bq_deviceAddress << 1, 3, 100);
            HAL_Delay(1000);
        }
#endif
//    }

    

    HAL_Delay(1500);
    BQAction_UpdateData();
    BQAction_TryUnsealedDevice();

    BQAction_SetManufacturingAllFet(false);
    BQAction_SetManufacturingFuse(false);
    BQAction_SetCalibration(false);
    BQAction_SetManufacturingGauging(true);
    BQAction_SetManufacturingPF(true);
    BQAction_SetManufacturingLF(true);
    BQAction_SetLed(false);

    BQAction_UpdateData();

    //BQ_ForceUpdateFlash();

    //BQ_BoundaryCellVoltage voltages = BQ_GetBoundaryCellVoltage();

//    ("[BQ] initialized", 16);
}

/**
 * @brief write data to flash
 * @param addr flash register
 * @param writeData short value to flash
 */
void BQ_WriteFlash(unsigned short addr, unsigned short writeData)
{
    unsigned char data[6];
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
void BQ_WriteFlashByte(unsigned short addr, unsigned char writeData)
{
    unsigned char data[5];
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
void BQ_WriteMABlockCommand(unsigned short command)
{
    // send 0x44, then count of bytes, then command
    unsigned char buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, buf, 4, 100);
}

/**
 * @brief reading from ManufacturerBlockAccess()
 * @param command command from read
 * @param receive array to receive
 * @param size array size
 */
void BQ_ReadMABlockCommand(unsigned short command, unsigned char *receive, unsigned char size)
{
    // send 0x44, then count of bytes, then command
    unsigned char buf[4] = {0x44, 0x02, command & 0xff, (command >> 8) & 0xff};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, buf, 4, 100);

    // send 0x44, then receive size
    unsigned char addr[2] = {0x44, 2 + size};
    HAL_I2C_Master_Transmit(bq_i2c, bq_deviceAddress << 1, addr, 2, 100);

    unsigned char result[35] = {0};
    HAL_I2C_Master_Receive(bq_i2c, bq_deviceAddress << 1, result, 35, 100);

    for (int i = 0; i < size; i++)
    {
        receive[i] = result[i + 3];
    }
}

/**
 * @brief reading from ManufacturerBlockAccess() as unsigned short
 * @param command command to read
 * @return 16bit value from command
 */
unsigned short BQ_ReadCommandAsShort(unsigned short command)
{
    unsigned char buf[2];

    BQ_ReadMABlockCommand(command, buf, 2);

    unsigned short result = 0;

    result = result | buf[0];
    result = result | (buf[1] << 8);

    return result;
}

/**
 * @brief reading from ManufacturerBlockAccess() as unsigned short
 * @param command command to read
 * @return 16bit value from command
 */
unsigned char BQ_ReadCommandAsChar(unsigned short command)
{
    unsigned char buf[1];

    BQ_ReadMABlockCommand(command, buf, 1);

    return buf[0];
}

/**
 * @brief reading from ManufacturerBlockAccess() as unsigned int
 * @param command command to read
 * @return 32bit value from command
 */
unsigned int BQ_ReadCommandAsInt(unsigned short command)
{
    unsigned char buf[4];

    BQ_ReadMABlockCommand(command, buf, 4);

    unsigned int result = 0;

    result = result | (buf[0]);
    result = result | (buf[1] << 8);
    result = result | (buf[2] << 16);
    result = result | (buf[3] << 24);

    return result;
}

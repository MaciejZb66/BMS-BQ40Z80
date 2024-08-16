#pragma once
#include <stdbool.h>
#include "bq40z80_mfa.h"
#include "i2c.h"
//#define CMD_CALIBRATION 0x002D
//#define CMD_MAN_FUSE 0x0026
//#define CMD_GAUGING 0x0021
//#define CMD_PF_EN 0x0024
//#define CMD_LF_EN 0x0023
//#define CMD_ALL_FET_EN 0x0022
//
//#define CMD_FET_DSG 0x0020
//#define CMD_FET_PDSG 0x001C
//#define CMD_FET_CHG 0x001F
//#define CMD_FET_PCHG 0x001E
//
//#define CMD_LED_TOGGLE 0x002B

void BQAction_SetLed(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetManufacturingAllFet(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetManufacturingFuse(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetCalibration(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetManufacturingGauging(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetManufacturingPF(I2C_HandleTypeDef *bq_i2c,bool active);
void BQAction_SetManufacturingLF(I2C_HandleTypeDef *bq_i2c,bool active);
bool BQAction_EnableCharging(I2C_HandleTypeDef *bq_i2c);
bool BQAction_EnableDischarging(I2C_HandleTypeDef *bq_i2c);
bool BQAction_EnablePreDischarging(I2C_HandleTypeDef *bq_i2c);
bool BQAction_DisableFets(I2C_HandleTypeDef *bq_i2c);

bool BQAction_TryUpdateFlash(I2C_HandleTypeDef *bq_i2c);
void BQAction_ForceUpdateFlash(I2C_HandleTypeDef *bq_i2c);

void BQAction_TryUnsealedDevice(I2C_HandleTypeDef *bq_i2c);
void BQAction_UpdateData(I2C_HandleTypeDef *bq_i2c);
void BQAction_UpdateOpStatus(I2C_HandleTypeDef *bq_i2c);


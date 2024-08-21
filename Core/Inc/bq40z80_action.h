#pragma once
#include <stdbool.h>
#include "bq40z80_data.h"
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

void BQAction_SetLed(BQ_data* BMS, bool active);
void BQAction_SetManufacturingAllFet(BQ_data* BMS, bool active);
void BQAction_SetManufacturingFuse(BQ_data* BMS, bool active);
void BQAction_SetCalibration(BQ_data* BMS, bool active);
void BQAction_SetManufacturingGauging(BQ_data* BMS, bool active);
void BQAction_SetManufacturingPF(BQ_data* BMS, bool active);
void BQAction_SetManufacturingLF(BQ_data* BMS, bool active);
bool BQAction_EnableCharging(BQ_data* BMS);
bool BQAction_EnableDischarging(BQ_data* BMS);
bool BQAction_EnablePreDischarging(BQ_data* BMS);
bool BQAction_DisableFets(BQ_data* BMS);

//bool BQAction_TryUpdateFlash(BQ_data BMS);
//void BQAction_ForceUpdateFlash(BQ_data BMS);

void BQAction_TryUnsealedDevice(BQ_data* BMS);
void BQAction_UpdateData(BQ_data* BMS);
void BQAction_UpdateOpStatus(BQ_data* BMS);


#pragma once
#include "stdbool.h"

#define CMD_CALIBRATION 0x002D
#define CMD_MAN_FUSE 0x0026
#define CMD_GAUGING 0x0021
#define CMD_PF_EN 0x0024
#define CMD_LF_EN 0x0023
#define CMD_ALL_FET_EN 0x0022

#define CMD_FET_DSG 0x0020
#define CMD_FET_PDSG 0x001C
#define CMD_FET_CHG 0x001F
#define CMD_FET_PCHG 0x001E

#define CMD_LED_TOGGLE 0x002B

#ifndef BQACTION_H
#define BQACTION_H

void BQAction_SetLed(bool active);
void BQAction_SetManufacturingAllFet(bool active);
void BQAction_SetManufacturingFuse(bool active);
void BQAction_SetCalibration(bool active);
void BQAction_SetManufacturingGauging(bool active);
void BQAction_SetManufacturingPF(bool active);
void BQAction_SetManufacturingLF(bool active);
bool BQAction_EnableCharging(void);
bool BQAction_EnableDischarging(void);
bool BQAction_EnablePreDischarging(void);
bool BQAction_DisableFets(void);

bool BQAction_TryUpdateFlash(void);
void BQAction_ForceUpdateFlash(void);

void BQAction_TryUnsealedDevice(void);
void BQAction_UpdateData(void);
void BQAction_UpdateOpStatus(void);

#endif

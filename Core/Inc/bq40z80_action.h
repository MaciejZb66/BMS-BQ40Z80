#pragma once
#include <stdbool.h>
#include "bq40z80_data.h"
#include "bq40z80_mfa.h"
#include "i2c.h"

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

void BQAction_TryUnsealedDevice(BQ_data* BMS);
void BQAction_UpdateData(BQ_data* BMS);
void BQAction_UpdateOpStatus(BQ_data* BMS);


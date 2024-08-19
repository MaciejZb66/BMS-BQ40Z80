#pragma once
#include "bq40z80_parser.h"
#include "bq40z80_data.h"
#include "i2c.h"
#include <stdbool.h>

typedef enum
{
	SEALED,
	UNSEALED,
	FULL_ACCESS,
	RESERVED
} SECURITY_MODE;

typedef enum
{
	RELAX,
	CHARGE,
	DISCHARGE
} CHARGE_MODE;

typedef struct
{
	uint16_t Minimum;
	uint16_t Maximum;
} BQ_BoundaryCellVoltage;


SECURITY_MODE BQ_GetSecurityMode(BQ_data BMS);
CHARGE_MODE BQ_GetChargeMode(BQ_data BMS);

BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(BQ_data BMS);

bool BQ_IsDischargeFetEnabled(BQ_data BMS);
bool BQ_IsChargeFetEnabled(BQ_data BMS);
bool BQ_IsDischargeFetTestEnabled(BQ_data BMS);
bool BQ_IsChargeFetTestEnabled(BQ_data BMS);
bool BQ_IsPreDischargeFetTestEnabled(BQ_data BMS);
bool BQ_IsPreChargeFetTestEnabled(BQ_data BMS);
bool BQ_IsDischargeEnabled(BQ_data BMS);
bool BQ_IsChargeEnabled(BQ_data BMS);
bool BQ_IsPreDischargeFetEnabled(BQ_data BMS);
bool BQ_IsPreChargeFetEnabled(BQ_data BMS);
bool BQ_IsManufacturingFuseEnabled(BQ_data BMS);
bool BQ_IsManufacturingAllFetEnabled(BQ_data BMS);
bool BQ_IsManufacturingGaugingEnabled(BQ_data BMS);
bool BQ_IsManufacturingCalibrationEnabled(BQ_data BMS);
bool BQ_IsManufacturingPermanentFailureEnabled(BQ_data BMS);
bool BQ_IsManufacturingLifetimeEnabled(BQ_data BMS);
bool BQ_IsLedEnabled(BQ_data BMS);

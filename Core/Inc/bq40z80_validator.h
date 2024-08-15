#pragma once
#include "bq40z80_parser.h"
#include "stdbool.h"

#ifndef BQVALID_H
#define BQVALID_H
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
	unsigned short Minimum;
	unsigned short Maximum;
} BQ_BoundaryCellVoltage;

#endif

SECURITY_MODE BQ_GetSecurityMode(void);
CHARGE_MODE BQ_GetChargeMode(void);

BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(void);

bool BQ_IsDischargeFetEnabled(void);
bool BQ_IsChargeFetEnabled(void);
bool BQ_IsDischargeFetTestEnabled(void);
bool BQ_IsChargeFetTestEnabled(void);
bool BQ_IsPreDischargeFetTestEnabled(void);
bool BQ_IsPreChargeFetTestEnabled(void);
bool BQ_IsDischargeEnabled(void);
bool BQ_IsChargeEnabled(void);
bool BQ_IsPreDischargeFetEnabled(void);
bool BQ_IsPreChargeFetEnabled(void);
bool BQ_IsManufacturingFuseEnabled(void);
bool BQ_IsManufacturingAllFetEnabled(void);
bool BQ_IsManufacturingGaugingEnabled(void);
bool BQ_IsManufacturingCalibrationEnabled(void);
bool BQ_IsManufacturingPermanentFailureEnabled(void);
bool BQ_IsManufacturingLifetimeEnabled(void);
bool BQ_IsLedEnabled(void);

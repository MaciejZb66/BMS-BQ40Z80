#pragma once
#include "bq40z80_parser.h"
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


SECURITY_MODE BQ_GetSecurityMode(void);
CHARGE_MODE BQ_GetChargeMode(I2C_HandleTypeDef *bq_i2c);

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

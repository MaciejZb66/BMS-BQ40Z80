#pragma once
#include "bq40z80_data.h"
#include "i2c.h"

#define KelvinToCelsius 2732

typedef enum{
	RESERVED,//00
	FULL_ACCESS,//01
	UNSEALED,//10
	SEALED//11
} SECURITY_MODE;

typedef enum{
	RELAX,
	CHARGE,
	DISCHARGE
} CHARGE_MODE;

typedef struct{
	uint16_t Min;
	uint16_t Max;
} BQ_BoundaryCellVoltage;

typedef struct{
	BQ_BoundaryCellVoltage balance;
	uint16_t voltage;
	int16_t current;
	uint8_t percentage;
	uint16_t fet_temperature;
	uint16_t cell_temperature;
} ToSendData;

CHARGE_MODE BQ_GetChargeMode(BQ_data* BMS);
BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(BQ_data* BMS);
void BQ_GetSendData(BQ_data* BMS, ToSendData* data);


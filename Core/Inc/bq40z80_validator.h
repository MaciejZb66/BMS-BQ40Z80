#pragma once
#include "bq40z80_data.h"
#include "i2c.h"

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

CHARGE_MODE BQ_GetChargeMode(BQ_data* BMS);



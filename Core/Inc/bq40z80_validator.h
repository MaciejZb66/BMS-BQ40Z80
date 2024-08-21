#pragma once
#include "bq40z80_parser.h"
#include "bq40z80_data.h"
#include "i2c.h"
#include <stdbool.h>

typedef enum{
	SEALED,
	UNSEALED,
	FULL_ACCESS,
	RESERVED
} SECURITY_MODE;

typedef enum{
	RELAX,
	CHARGE,
	DISCHARGE
} CHARGE_MODE;

SECURITY_MODE BQ_GetSecurityMode(BQ_data* BMS);
CHARGE_MODE BQ_GetChargeMode(BQ_data* BMS);



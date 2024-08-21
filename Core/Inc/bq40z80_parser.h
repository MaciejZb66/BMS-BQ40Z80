#pragma once
#include <stdint.h>
#include "bq40z80_data.h"
/**
 * @attention bits from high to low
 * 15bit in datasheet - 0 bit in array
 */
extern BQ_data BMS_1;

void BQ_ParseAllFlags(BQ_data* BMS,
					  uint32_t opStatus,
					  uint16_t batteryStatus,
					  uint16_t batteryMode,
					  uint8_t gpio,
					  uint16_t manStatus,
					  uint32_t chargeStatus,
					  uint32_t gaugStatus);
void BQ_ParseOperationStatus(BQ_data* BMS, uint32_t raw);
void BQ_ParseChargeStatus(BQ_data* BMS, uint32_t raw);
void BQ_ParseGaugeStatus(BQ_data* BMS, uint32_t raw);
void BQ_ParseBatteryStatus(BQ_data* BMS, uint16_t raw);
void BQ_ParseBatteryMode(BQ_data* BMS, uint16_t raw);
void BQ_ParseManufacturingStatus(BQ_data* BMS, uint16_t raw);

void BQ_ParseGpio(BQ_data* BMS, uint8_t raw);

#pragma once
#include <stdint.h>
#include "bq40z80_data.h"
/**
 * @attention bits from high to low
 * 15bit in datasheet - 0 bit in array
 */
//extern uint8_t BQ_opStatus[32];
//extern uint8_t BQ_chargeStatus[32];
//extern uint8_t BQ_gaugeStatus[32];
//
//extern uint8_t BQ_batteryStatus[16];
//extern uint8_t BQ_batteryMode[16];
//extern uint8_t BQ_manufacturingStatus[16];
//extern uint8_t BQ_gpio[8];

// bits from low to high
// filled in externally
//extern uint8_t BQ_daStatus1[32];
//extern uint8_t BQ_daStatus2[16];
//extern uint8_t BQ_daStatus3[18];
//extern uint8_t BQ_outCal[32];
//extern BQ_data BMS_1;

void BQ_ParseAllFlags(BQ_data BMS,
					  uint32_t opStatus,
					  uint16_t batteryStatus,
					  uint16_t batteryMode,
					  uint8_t gpio,
					  uint16_t manStatus,
					  uint32_t chargeStatus,
					  uint32_t gaugStatus);
void BQ_ParseOperationStatus(BQ_data BMS, uint32_t raw);
void BQ_ParseChargeStatus(BQ_data BMS, uint32_t raw);
void BQ_ParseGaugeStatus(BQ_data BMS, uint32_t raw);
void BQ_ParseBatteryStatus(BQ_data BMS, uint16_t raw);
void BQ_ParseBatteryMode(BQ_data BMS, uint16_t raw);
void BQ_ParseManufacturingStatus(BQ_data BMS, uint16_t raw);

void BQ_ParseGpio(BQ_data BMS, uint8_t raw);

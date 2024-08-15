//#include "pretty_printer.h"
#pragma once
/**
 * @attention bits from high to low
 * 15bit in datasheet - 0 bit in array
 */
extern unsigned char BQ_opStatus[32];
extern unsigned char BQ_chargeStatus[32];
extern unsigned char BQ_gaugeStatus[32];
extern unsigned char BQ_batteryStatus[16];
extern unsigned char BQ_batteryMode[16];
extern unsigned char BQ_manufacturingStatus[16];
extern unsigned char BQ_gpio[8];

// bits from low to high
// filled in externally
extern unsigned char BQ_daStatus1[32];
extern unsigned char BQ_daStatus2[16];
extern unsigned char BQ_daStatus3[18];
extern unsigned char BQ_outCal[32];

void BQ_ParseAllFlags(unsigned int opStatus,
					  unsigned short batteryStatus,
					  unsigned short batteryMode,
					  unsigned char gpio,
					  unsigned short manStatus,
					  unsigned int chargeStatus,
					  unsigned int gaugStatus);
void BQ_ParseOperationStatus(unsigned int raw);
void BQ_ParseChargeStatus(unsigned int raw);
void BQ_ParseGaugeStatus(unsigned int raw);
void BQ_ParseBatteryStatus(unsigned short raw);
void BQ_ParseBatteryMode(unsigned short raw);
void BQ_ParseManufacturingStatus(unsigned short raw);

void BQ_ParseGpio(unsigned char raw);

//#pragma once
//#pragma message("bq40z80_data.h is included")
#include "i2c.h"
#include <stdint.h>

/**
 * @attention
 * in datasheet some registers are binary number, in which each bit has a unique meaning
 * example: opStatus have 32 bits, 8-9 bits indicate security mode. etc.
 *
 * @warning: in array values: '1' = 49, '0' = 48
 */
#ifndef BQ40Z80_DATA_H
#define BQ40Z80_DATA_H
//#pragma message("struct included")
typedef struct{
	I2C_HandleTypeDef *bq_i2c;
	uint8_t BQ_opStatus[32]; //0x0054(s)
	uint8_t BQ_chargeStatus[32]; //0x0055(s)
	uint8_t BQ_gaugeStatus[32]; //0x0056?
	uint8_t BQ_batteryStatus[16];
	uint8_t BQ_batteryMode[16];

	uint8_t BQ_manufacturingStatus[16]; //0x0057?
	uint8_t BQ_gpio[8];
	uint8_t BQ_daStatus1[32]; //0x0071(s)
	uint8_t BQ_daStatus2[16]; //0x0072(s)
	uint8_t BQ_daStatus3[18]; //0x007B(s)
	uint8_t BQ_outCal[32]; //0xF081
}BQ_data;

#endif // BQ40Z80_DATA_H


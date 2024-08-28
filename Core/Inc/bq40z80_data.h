//#pragma once
//#pragma message("bq40z80_data.h is included")
#include "i2c.h"
#include <stdint.h>
#include "bq40z80_registers.h"
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

typedef union{
	OPERATION_STATUS bits;
	uint32_t all;
}OP_STATUS;

typedef union{
	MANUFACTURING_STATUS bits;
	uint16_t all;
}MAN_STATUS;

typedef union{
	BATTERY_STATUS bits;
	uint16_t all;
}BAT_STATUS;

typedef union{
	BATTERY_MODE bits;
	uint16_t all;
}BAT_MODE;

typedef union{
	CHARGING_STATUS bits;
	uint32_t all;
}CHG_STATUS;

typedef union{
	GAUGING_STATUS bits;
	uint32_t all;
}GUG_STATUS;

typedef union{
	DA_STATUS_1 sep;
	uint8_t all[32];
}DAS_1;

typedef union{
	DA_STATUS_2 sep;
	uint8_t all[16];
}DAS_2;

typedef union{
	DA_STATUS_3 sep;
	uint8_t all[18];
}DAS_3;

typedef union{
	OUTPUT_ADC_CAL sep;
	uint8_t all[32];
}OUTCAL;

typedef union{
	GPIO bits;
	uint8_t all;
}GP;

typedef struct{
	I2C_HandleTypeDef *bq_i2c;
	uint8_t bq_deviceAddress;
	OP_STATUS BQ_opStatus;				//M0x0054
	CHG_STATUS BQ_chargeStatus;			//M0x0055
	GUG_STATUS BQ_gaugeStatus;			//M0x0056
	BAT_STATUS BQ_batteryStatus;		//0x16
	BAT_MODE BQ_batteryMode;			//0x03

	MAN_STATUS BQ_manufacturingStatus;	//M0x0057
	GP BQ_gpio;							//0x48
	DAS_1 BQ_daStatus1;					//M0x0071
	DAS_2 BQ_daStatus2;					//M0x0072
	DAS_3 BQ_daStatus3;					//M0x007B
	OUTCAL BQ_outCal;					//M0xF081
}BQ_data;

#endif // BQ40Z80_DATA_H


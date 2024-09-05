#include "i2c.h"
#include <stdint.h>
#include "bq40z80_registers.h"


//-----------Include here USED_I2Cx-------------
#define USED_I2C1
//#define USED_I2C2
//#define USED_I2C3
//----------------------------------------------

#ifndef BQ40Z80_DATA_H
#define BQ40Z80_DATA_H

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

typedef enum{
	CONNECTED,
	CHANGED_ADDRESS,
	INVALID_DEVICE,
	NEED_RESET
}CONNECTION_STATUS;

typedef struct{
	uint16_t Min;
	uint16_t Max;
} BQ_BoundaryCellVoltage;

typedef struct{
	BQ_BoundaryCellVoltage balance;//not yet transmitted
	uint16_t voltage; //not yet transmitted
	int16_t current;
	uint8_t percentage; //not yet transmitted
	uint16_t fet_temperature;
	uint16_t cell_temperature;
} ToSendData;

typedef struct{
	I2C_HandleTypeDef *bq_i2c;
	uint8_t bq_deviceAddress;
	ToSendData data;
	CONNECTION_STATUS connection;

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


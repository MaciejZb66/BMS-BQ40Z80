#include "bq40z80_parser.h"

/**
 * @attention 
 * in datasheet some registers are binary number, in which each bit has a unique meaning
 * example: opStatus have 32 bits, 8-9 bits indicate security mode. etc.
 * 
 * @warning: in array values: '1' = 49, '0' = 48
 */
unsigned char BQ_opStatus[32] = {0};
unsigned char BQ_chargeStatus[32] = {0};
unsigned char BQ_gaugeStatus[32] = {0};
unsigned char BQ_batteryStatus[16] = {0};
unsigned char BQ_batteryMode[16] = {0};
unsigned char BQ_manufacturingStatus[16] = {0};
unsigned char BQ_gpio[8] = {0};
unsigned char BQ_daStatus1[32] = {0};
unsigned char BQ_daStatus2[16] = {0};
unsigned char BQ_daStatus3[18] = {0};
unsigned char BQ_outCal[32] = {0};

/**
 * @brief convert decimal value to binary array, array[0] - first element
 * @param value decimal value
 * @param array array to write
 * @param count array size
 */
void decimalToBinary(unsigned int value, unsigned char *array, unsigned char count)
{
	unsigned char currentCount = 0;
	while (value > 0)
	{
		array[currentCount] = value % 2;
		value /= 2;
		currentCount++;
	}

	while (currentCount < count)
	{
		array[currentCount] = 0;
		currentCount++;
	}
}

/**
 * @brief parse all values to flags array
 * @param opStatus operationStatus value from BQ
 * @param batteryStatus batteryStatus value from BQ
 * @param batteryMode batteryMode value from BQ
 * @param gpio GPIORead value from BQ
 * @param manStatus manufacturingStatus value from BQ
 * @param chargeStatus chargingStatus value from BQ
 * @param gaugStatus gaugingStatus value from BQ
 **/
void BQ_ParseAllFlags(unsigned int opStatus,
					  unsigned short batteryStatus,
					  unsigned short batteryMode,
					  unsigned char gpio,
					  unsigned short manStatus,
					  unsigned int chargeStatus,
					  unsigned int gaugStatus)
{
	BQ_ParseOperationStatus(opStatus);
	BQ_ParseChargeStatus(chargeStatus);
	BQ_ParseGaugeStatus(gaugStatus);
	BQ_ParseBatteryStatus(batteryStatus);
	BQ_ParseManufacturingStatus(manStatus);
	BQ_ParseBatteryMode(batteryMode);
	BQ_ParseGpio(gpio);
}
void BQ_ParseOperationStatus(unsigned int raw)
{
	//convert to binary array and save in BQ_opStatus
	decimalToBinary(raw, BQ_opStatus, 32);
}

void BQ_ParseChargeStatus(unsigned int raw)
{
	//convert to binary array and save in BQ_chargeStatus
	decimalToBinary(raw, BQ_chargeStatus, 32);
}

void BQ_ParseGaugeStatus(unsigned int raw)
{
	//convert to binary array and save in BQ_gaugeStatus
	decimalToBinary(raw, BQ_gaugeStatus, 32);
}

void BQ_ParseBatteryStatus(unsigned short raw)
{
	//convert to binary array and save in BQ_batteryStatus
	decimalToBinary(raw, BQ_batteryStatus, 16);
}

void BQ_ParseBatteryMode(unsigned short raw)
{
	//convert to binary array and save in BQ_batteryMode
	decimalToBinary(raw, BQ_batteryMode, 16);
}

void BQ_ParseManufacturingStatus(unsigned short raw)
{
	decimalToBinary(raw, BQ_manufacturingStatus, 16);
}

void BQ_ParseGpio(unsigned char raw)
{
	//convert to binary array and save in BQ_gpio
	decimalToBinary(raw, BQ_gpio, 8);
}
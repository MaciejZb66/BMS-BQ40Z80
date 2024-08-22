#include "bq40z80_parser.h"

/**
 * @brief convert decimal value to binary array, array[0] - first element
 * @param value decimal value
 * @param array array to write
 * @param count array size
 */
void decimalToBinary(uint32_t value, uint8_t *array, uint8_t count) //LSB is on array[0]
{
	uint8_t currentCount = 0;
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
void BQ_ParseAllFlags(BQ_data* BMS,
					  uint32_t opStatus,
					  uint16_t batteryStatus,
					  uint16_t batteryMode,
					  uint8_t gpio,
					  uint16_t manStatus,
					  uint32_t chargeStatus,
					  uint32_t gaugStatus)
{
	BQ_ParseOperationStatus(BMS, opStatus);
	BQ_ParseChargeStatus(BMS, chargeStatus);
	BQ_ParseGaugeStatus(BMS, gaugStatus);
	BQ_ParseBatteryStatus(BMS, batteryStatus);
	BQ_ParseManufacturingStatus(BMS, manStatus);
	BQ_ParseBatteryMode(BMS, batteryMode);
	BQ_ParseGpio(BMS, gpio);
}
void BQ_ParseOperationStatus(BQ_data* BMS, uint32_t raw)
{
	//convert to binary array and save in BQ_opStatus
	BMS->BQ_opStatus.all = raw;
}

void BQ_ParseChargeStatus(BQ_data* BMS, uint32_t raw)
{
	//convert to binary array and save in BQ_chargeStatus
	decimalToBinary(raw, BMS->BQ_chargeStatus, 32);
}

void BQ_ParseGaugeStatus(BQ_data* BMS, uint32_t raw)
{
	//convert to binary array and save in BQ_gaugeStatus
	decimalToBinary(raw, BMS->BQ_gaugeStatus, 32);
}

void BQ_ParseBatteryStatus(BQ_data* BMS, uint16_t raw)
{
	//convert to binary array and save in BQ_batteryStatus
//	decimalToBinary(raw, BMS->BQ_batteryStatus, 16);
	BMS->BQ_batteryStatus.all = raw;
}

void BQ_ParseBatteryMode(BQ_data* BMS, uint16_t raw)
{
	//convert to binary array and save in BQ_batteryMode
//	decimalToBinary(raw, BMS->BQ_batteryMode, 16);
	BMS->BQ_batteryMode.all = raw;
}

void BQ_ParseManufacturingStatus(BQ_data* BMS, uint16_t raw)
{
	BMS->BQ_manufacturingStatus.all = raw;
}

void BQ_ParseGpio(BQ_data* BMS, uint8_t raw)
{
	//convert to binary array and save in BQ_gpio
	decimalToBinary(raw, BMS->BQ_gpio, 8);
}

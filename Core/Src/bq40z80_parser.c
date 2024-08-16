#include "bq40z80_parser.h"

/**
 * @brief convert decimal value to binary array, array[0] - first element
 * @param value decimal value
 * @param array array to write
 * @param count array size
 */
void decimalToBinary(uint32_t value, uint8_t *array, uint8_t count)
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
void BQ_ParseAllFlags(uint32_t opStatus,
					  uint16_t batteryStatus,
					  uint16_t batteryMode,
					  uint8_t gpio,
					  uint16_t manStatus,
					  uint32_t chargeStatus,
					  uint32_t gaugStatus)
{
	BQ_ParseOperationStatus(opStatus);
	BQ_ParseChargeStatus(chargeStatus);
	BQ_ParseGaugeStatus(gaugStatus);
	BQ_ParseBatteryStatus(batteryStatus);
	BQ_ParseManufacturingStatus(manStatus);
	BQ_ParseBatteryMode(batteryMode);
	BQ_ParseGpio(gpio);
}
void BQ_ParseOperationStatus(uint32_t raw)
{
	//convert to binary array and save in BQ_opStatus
	decimalToBinary(raw, BMS_1.BQ_opStatus, 32);
}

void BQ_ParseChargeStatus(uint32_t raw)
{
	//convert to binary array and save in BQ_chargeStatus
	decimalToBinary(raw, BMS_1.BQ_chargeStatus, 32);
}

void BQ_ParseGaugeStatus(uint32_t raw)
{
	//convert to binary array and save in BQ_gaugeStatus
	decimalToBinary(raw, BMS_1.BQ_gaugeStatus, 32);
}

void BQ_ParseBatteryStatus(uint16_t raw)
{
	//convert to binary array and save in BQ_batteryStatus
	decimalToBinary(raw, BMS_1.BQ_batteryStatus, 16);
}

void BQ_ParseBatteryMode(uint16_t raw)
{
	//convert to binary array and save in BQ_batteryMode
	decimalToBinary(raw, BMS_1.BQ_batteryMode, 16);
}

void BQ_ParseManufacturingStatus(uint16_t raw)
{
	decimalToBinary(raw, BMS_1.BQ_manufacturingStatus, 16);
}

void BQ_ParseGpio(uint8_t raw)
{
	//convert to binary array and save in BQ_gpio
	decimalToBinary(raw, BMS_1.BQ_gpio, 8);
}

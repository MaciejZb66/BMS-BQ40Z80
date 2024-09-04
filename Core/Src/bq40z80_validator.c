#include "bq40z80_validator.h"
#include "bq40z80.h"



/**
 * @brief get charge from BQ_opStatus
 * @return CHARGE, DISCHARGE or RELAX
 */
CHARGE_MODE BQ_GetChargeMode(BQ_data* BMS)
{
    BQAction_UpdateOpStatus(BMS);
    uint16_t packVoltage = BMS->BQ_daStatus1.sep.pack_voltage;
    uint16_t current = I2CHelper_ReadRegisterAsShort(BMS, BQ40Z80_SBS_Current);

    if (packVoltage > 1000 && BMS->BQ_opStatus.bits.chg && BMS->BQ_opStatus.bits.pchg && BMS->BQ_manufacturingStatus.bits.chg && current > 0 && current < 30000){
        return CHARGE;
    }else if (packVoltage > 1000 && BMS->BQ_opStatus.bits.xdsg && BMS->BQ_opStatus.bits.dsg && BMS->BQ_manufacturingStatus.bits.dsg && 65535 - current > 0 && current > 30000){
        return DISCHARGE;
    }else{
        return RELAX;
    }
}

BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(BQ_data* BMS)
{
    BQ_BoundaryCellVoltage result;
    result.Max = 0;
    result.Min = 65535;

    uint16_t cells[6] =
        {
			BMS->BQ_daStatus1.sep.cell_voltage_1, // 1
			BMS->BQ_daStatus1.sep.cell_voltage_2, // 2
            BMS->BQ_daStatus1.sep.cell_voltage_3, // 3
            BMS->BQ_daStatus1.sep.cell_voltage_4, // 4
            BMS->BQ_daStatus3.sep.cell_voltage_5, // 5
            BMS->BQ_daStatus3.sep.cell_voltage_6  // 6
        };

    for (int i = 0; i < 6; i++)
    {
        if (cells[i] > result.Max)
        {
            result.Max = cells[i];
        }
        if (cells[i] < result.Min)
        {
            result.Min = cells[i];
        }
    }

    return result;
}

void BQ_GetSendData(BQ_data* BMS){
	BMS->data.voltage = I2CHelper_ReadRegisterAsShort(BMS, BQ40Z80_SBS_Voltage);
	BMS->data.current = BMS->BQ_outCal.sep.current;
	BMS->data.balance = BQ_GetBoundaryCellVoltage(BMS);
	BMS->data.cell_temperature = BMS->BQ_daStatus2.sep.ts1_temperature - KelvinToCelsius;
	BMS->data.fet_temperature = BMS->BQ_daStatus2.sep.ts2_temperature - KelvinToCelsius;
	BMS->data.percentage = I2CHelper_ReadRegisterAsChar(BMS, BQ40Z80_SBS_RelativeStateOfCharge);
}


#include "bq40z80_validator.h"
#include "bq40z80.h"

/** 
 * @attention bq40z80_validator gets data from bq40z80_parser!
 * you must update the data first in bq40z80_parser using
 */

/**
 * @brief get security mode from BQ_opStatus
 * @return SECURITY_MODE
 */
SECURITY_MODE BQ_GetSecurityMode(void)
{
    if (BMS_1.BQ_opStatus[9] && BMS_1.BQ_opStatus[8]){
        return SEALED;//11
    }else if (BMS_1.BQ_opStatus[9] && !BMS_1.BQ_opStatus[8]){
        return UNSEALED;//10
    }else if (!BMS_1.BQ_opStatus[9] && BMS_1.BQ_opStatus[8]){
        return FULL_ACCESS;//01
    }else{
        return RESERVED;//00
    }
}

/**
 * @brief get charge from BQ_opStatus
 * @return CHARGE, DISCHARGE or RELAX
 */
CHARGE_MODE BQ_GetChargeMode(BQ_data BMS)
{
    BQAction_UpdateOpStatus(BMS);
    uint16_t packVoltage = BMS_1.BQ_daStatus1[10] | (BMS_1.BQ_daStatus1[11] << 8);
    uint16_t current = I2CHelper_ReadRegisterAsShort(BMS.bq_i2c, bq_deviceAddress, BQ40Z80_SBS_Current);

    if (packVoltage > 1000 && BQ_IsChargeEnabled() && BQ_IsChargeFetEnabled() && BQ_IsChargeFetTestEnabled() && current > 0 && current < 30000){
        return CHARGE;
    }else if (packVoltage > 1000 && BQ_IsDischargeEnabled() && BQ_IsDischargeFetEnabled() && BQ_IsDischargeFetTestEnabled() && 65535 - current > 0 && current > 30000){
        return DISCHARGE;
    }else{
        return RELAX;
    }
}

/**
 * @brief get minimum and maximum cell voltage
 * @return BQ_BoundaryCellVoltage struct
 */
BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(void)
{
    BQ_BoundaryCellVoltage result;
    result.Maximum = 0;
    result.Minimum = 65535;

    uint16_t cells[6] =
        {
			BMS_1.BQ_daStatus1[0] | (BMS_1.BQ_daStatus1[1] << 8), // 1
			BMS_1.BQ_daStatus1[2] | (BMS_1.BQ_daStatus1[3] << 8), // 2
			BMS_1.BQ_daStatus1[4] | (BMS_1.BQ_daStatus1[5] << 8), // 3
			BMS_1.BQ_daStatus1[6] | (BMS_1.BQ_daStatus1[7] << 8), // 4
			BMS_1.BQ_daStatus3[0] | (BMS_1.BQ_daStatus3[1] << 8), // 5
			BMS_1.BQ_daStatus3[2] | (BMS_1.BQ_daStatus3[3] << 8)  // 6
        };

    for (int i = 0; i < 6; i++)
    {
        if (cells[i] > result.Maximum)
        {
            result.Maximum = cells[i];
        }
        if (cells[i] < result.Minimum)
        {
            result.Minimum = cells[i];
        }
    }

    return result;
}

bool BQ_IsDischargeFetEnabled(void)
{
    return BMS_1.BQ_opStatus[1];
}

bool BQ_IsChargeFetEnabled(void)
{
    return BMS_1.BQ_opStatus[2];
}

bool BQ_IsPreChargeFetEnabled(void)
{
    return BMS_1.BQ_opStatus[3];
}



bool BQ_IsDischargeEnabled(void)
{
    return BMS_1.BQ_opStatus[13];
}

bool BQ_IsChargeEnabled(void)
{
    return BMS_1.BQ_opStatus[14];
}

bool BQ_IsPreDischargeFetEnabled(void)
{
    return BMS_1.BQ_opStatus[4];
}



bool BQ_IsManufacturingFuseEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[8];
}

bool BQ_IsDischargeFetTestEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[2];
}

bool BQ_IsChargeFetTestEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[1];
}

bool BQ_IsPreDischargeFetTestEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[13];
}

bool BQ_IsPreChargeFetTestEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[0];
}

/**
 * @brief function shows fet control
 * @return 0 if fet control enabled, 1 if fet control disabled
 */
bool BQ_IsManufacturingAllFetEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[4];
}

bool BQ_IsManufacturingGaugingEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[3];
}

bool BQ_IsManufacturingCalibrationEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[15];
}

bool BQ_IsManufacturingPermanentFailureEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[6];
}

bool BQ_IsManufacturingLifetimeEnabled(void)
{
    return BMS_1.BQ_manufacturingStatus[5];
}

bool BQ_IsLedEnabled(void)
{
    return BMS_1.BQ_opStatus[17];
}

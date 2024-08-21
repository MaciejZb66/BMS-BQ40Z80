#include "bq40z80_validator.h"
#include "bq40z80.h"

extern BQ_data BMS_1;
/** 
 * @attention bq40z80_validator gets data from bq40z80_parser!
 * you must update the data first in bq40z80_parser using
 */

/**
 * @brief get security mode from BQ_opStatus
 * @return SECURITY_MODE
 */
SECURITY_MODE BQ_GetSecurityMode(BQ_data* BMS)
{
    if (BMS->BQ_opStatus.bits.sec1 && BMS->BQ_opStatus.bits.sec0){
        return SEALED;//11
    }else if (BMS->BQ_opStatus.bits.sec1 && !BMS->BQ_opStatus.bits.sec0){
        return UNSEALED;//10
    }else if (!BMS->BQ_opStatus.bits.sec1 && BMS->BQ_opStatus.bits.sec0){
        return FULL_ACCESS;//01
    }else{
        return RESERVED;//00
    }
}

/**
 * @brief get charge from BQ_opStatus
 * @return CHARGE, DISCHARGE or RELAX
 */
CHARGE_MODE BQ_GetChargeMode(BQ_data* BMS)
{
    BQAction_UpdateOpStatus(BMS);
    uint16_t packVoltage = BMS->BQ_daStatus1[10] | (BMS->BQ_daStatus1[11] << 8);
    uint16_t current = I2CHelper_ReadRegisterAsShort(BMS->bq_i2c, bq_deviceAddress, BQ40Z80_SBS_Current);

    if (packVoltage > 1000 && BMS->BQ_opStatus.bits.chg && BMS->BQ_opStatus.bits.pchg && BQ_IsChargeFetTestEnabled(BMS) && current > 0 && current < 30000){
        return CHARGE;
    }else if (packVoltage > 1000 && BMS->BQ_opStatus.bits.xdsg && BMS->BQ_opStatus.bits.dsg && BQ_IsDischargeFetTestEnabled(BMS) && 65535 - current > 0 && current > 30000){
        return DISCHARGE;
    }else{
        return RELAX;
    }
}

/**
 * @brief get minimum and maximum cell voltage
 * @return BQ_BoundaryCellVoltage struct
 */
//BQ_BoundaryCellVoltage BQ_GetBoundaryCellVoltage(BQ_data BMS)
//{
//    BQ_BoundaryCellVoltage result;
//    result.Maximum = 0;
//    result.Minimum = 65535;
//
//    uint16_t cells[6] =
//        {
//			BMS.BQ_daStatus1[0] | (BMS.BQ_daStatus1[1] << 8), // 1
//			BMS.BQ_daStatus1[2] | (BMS.BQ_daStatus1[3] << 8), // 2
//			BMS.BQ_daStatus1[4] | (BMS.BQ_daStatus1[5] << 8), // 3
//			BMS.BQ_daStatus1[6] | (BMS.BQ_daStatus1[7] << 8), // 4
//			BMS.BQ_daStatus3[0] | (BMS.BQ_daStatus3[1] << 8), // 5
//			BMS.BQ_daStatus3[2] | (BMS.BQ_daStatus3[3] << 8)  // 6
//        };
//
//    for (int i = 0; i < 6; i++)
//    {
//        if (cells[i] > result.Maximum)
//        {
//            result.Maximum = cells[i];
//        }
//        if (cells[i] < result.Minimum)
//        {
//            result.Minimum = cells[i];
//        }
//    }
//
//    return result;
//}

//bool BQ_IsDischargeFetEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.dsg;
//}

//bool BQ_IsChargeFetEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.chg;
//}

//bool BQ_IsPreChargeFetEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.pchg;
//}

//bool BQ_IsPreDischargeFetEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.pdsg;
//}
//
//bool BQ_IsDischargeEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.xdsg;
//}
//
//bool BQ_IsChargeEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.xchg;
//}
//
//bool BQ_IsLedEnabled(BQ_data BMS)
//{
//    return BMS.BQ_opStatus.bits.led;
//}

bool BQ_IsPreChargeFetTestEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.pchg;
}

bool BQ_IsChargeFetTestEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.chg;
}

bool BQ_IsDischargeFetTestEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.dsg;
}

bool BQ_IsManufacturingGaugingEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.gauge;
}

/**
 * @brief function shows fet control
 * @return 0 if fet control enabled, 1 if fet control disabled
 */
bool BQ_IsManufacturingAllFetEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.fet;
}

bool BQ_IsManufacturingLifetimeEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.lf;
}

bool BQ_IsManufacturingPermanentFailureEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.pf;
}

bool BQ_IsManufacturingFuseEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.fuse;
}

bool BQ_IsPreDischargeFetTestEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.pdsg;
}

bool BQ_IsManufacturingCalibrationEnabled(BQ_data* BMS)
{
    return BMS->BQ_manufacturingStatus.bits.cal;
}

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

    if (packVoltage > 1000 && BMS->BQ_opStatus.bits.chg && BMS->BQ_opStatus.bits.pchg && BMS->BQ_manufacturingStatus.bits.chg && current > 0 && current < 30000){
        return CHARGE;
    }else if (packVoltage > 1000 && BMS->BQ_opStatus.bits.xdsg && BMS->BQ_opStatus.bits.dsg && BMS->BQ_manufacturingStatus.bits.dsg && 65535 - current > 0 && current > 30000){
        return DISCHARGE;
    }else{
        return RELAX;
    }
}

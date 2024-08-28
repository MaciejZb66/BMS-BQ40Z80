#include "bq40z80_validator.h"
#include "bq40z80.h"

extern BQ_data BMS_1;


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

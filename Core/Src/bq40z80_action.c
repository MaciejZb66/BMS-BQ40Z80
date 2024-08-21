#include "bq40z80_action.h"
#include "bq40z80.h"


extern BQ_data BMS_1;
/**
 * @brief setting led
 * @param active true - set on, false - set off
 */
void BQAction_SetLed(BQ_data* BMS, bool active)
{
    if (BMS->BQ_opStatus.bits.led != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_LED_TOGGLE);
    }
}

/**
 * @brief setting ManufacturingStatus()[FET_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingAllFet(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.fet != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_FET_CONTROL);
    }
}

/**
 * @brief setting ManufacturingStatus()[FUSE_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingFuse(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.fuse != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_FUSE);
    }
}
/**
 * @brief setting ManufacturingStatus()[CAL_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetCalibration(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.cal != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CALIBRATION_MODE);
    }
}

/**
 * @brief setting ManufacturingStatus()[GAUGE_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingGauging(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.gauge != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_GAUGING);
    }
}
/**
 * @brief setting ManufacturingStatus()[PF_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingPF(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.pf != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PERMANENT_FAILURE);
    }
}
/**
 * @brief setting ManufacturingStatus()[LF_EN] lifetime
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingLF(BQ_data* BMS, bool active)
{
    if (BMS->BQ_manufacturingStatus.bits.lf != active)
    {
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_LIFETIME_DATA_COLLECTION);
    }
}

/**
 * @brief enable charge fet and disable the rest
 * @param none
 */
bool BQAction_EnableCharging(BQ_data* BMS)
{
    if (BQ_GetChargeMode(BMS) == CHARGE){
        return false;
    }

    // turn off unused fets
    if (BMS->BQ_manufacturingStatus.bits.dsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pdsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pchg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on charge
    if (!BMS->BQ_manufacturingStatus.bits.chg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CHG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode(BMS) == CHARGE){
        return true;
    }else{
        // turn off charge
        if (BMS->BQ_manufacturingStatus.bits.chg){
            BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CHG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief enable discharge fet and disable the rest
 * @param none
 */
bool BQAction_EnableDischarging(BQ_data* BMS)
{
    if (BQ_GetChargeMode(BMS) == DISCHARGE){
        return false;
    }

    // turn off unused fets
    if (BMS->BQ_manufacturingStatus.bits.chg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pdsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pchg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on discharge
    if (!BMS->BQ_manufacturingStatus.bits.dsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_DSG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode(BMS) != CHARGE){
        return true;
    }else{
        // turn off discharge
        if (BMS->BQ_manufacturingStatus.bits.dsg){
            BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_DSG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief enable predischarge fet and disable the rest
 * @param none
 */
bool BQAction_EnablePreDischarging(BQ_data* BMS)
{
    if (BQ_GetChargeMode(BMS) == DISCHARGE){
        return false;
    }

    // turn off unused fets
    if (BMS->BQ_manufacturingStatus.bits.chg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.dsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pchg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on pre-discharge
    if (!BMS->BQ_manufacturingStatus.bits.pdsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode(BMS) != CHARGE){
        return true;
    }
    else
    {
        // turn off pre-discharge
        if (BMS->BQ_manufacturingStatus.bits.pdsg){
            BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PDSG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief disable all fets
 * @param none
 */
bool BQAction_DisableFets(BQ_data* BMS)
{
    BQAction_UpdateOpStatus(BMS);
    if (BMS->BQ_manufacturingStatus.bits.chg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.dsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pchg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }
    if (BMS->BQ_manufacturingStatus.bits.pdsg){
        BQ_WriteMABlockCommand(BMS, BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }

    return true;
}

/**
 * @brief change sealed mode to unsealed
 * @param none
 **/
void BQAction_TryUnsealedDevice(BQ_data* BMS)
{
    BQAction_UpdateOpStatus(BMS);
    SECURITY_MODE securityMode = BQ_GetSecurityMode(BMS);
    while (securityMode == SEALED || securityMode == RESERVED)
    {
        BQ_WriteMABlockCommand(BMS, 0x0414);
        HAL_Delay(500);
        BQ_WriteMABlockCommand(BMS, 0x3672);
        HAL_Delay(3000);
        BQAction_UpdateOpStatus(BMS);
        securityMode = BQ_GetSecurityMode(BMS);
    }
}

/**
 * @brief updating statuses, flags
 * @param none
 */
void BQAction_UpdateData(BQ_data* BMS)
{
    uint16_t manStatus = BQ_ReadCommandAsLShort(BMS, BQ40Z80_MFA_MANUFACTURING_STATUS);
    BMS->BQ_manufacturingStatus.all = manStatus;
    uint32_t chargeStatus = BQ_ReadCommandAsInt(BMS, BQ40Z80_MFA_CHARGING_STATUS);
    uint32_t operationStatus = BQ_ReadCommandAsLInt(BMS, BQ40Z80_MFA_OPERATION_STATUS);
    BMS->BQ_opStatus.all= operationStatus;
    uint32_t gaugStatus = BQ_ReadCommandAsInt(BMS, BQ40Z80_MFA_GAUGING_STATUS);

    uint16_t batteryMode = I2CHelper_ReadRegisterAsShort(BMS->bq_i2c, bq_deviceAddress, BQ40Z80_SBS_BatteryMode);
    uint16_t batteryStatus = I2CHelper_ReadRegisterAsShort(BMS->bq_i2c, bq_deviceAddress, BQ40Z80_SBS_BatteryStatus);
    uint8_t gpioStatus = I2CHelper_ReadRegisterAsChar(BMS->bq_i2c, bq_deviceAddress, BQ40Z80_SBS_GPIORead);

    BQ_ReadMABlockCommand(BMS, BQ40Z80_MFA_DA_STATUS_1, BMS_1.BQ_daStatus1, 32);
    BQ_ReadMABlockCommand(BMS, BQ40Z80_MFA_DA_STATUS_2, BMS_1.BQ_daStatus2, 16);
    BQ_ReadMABlockCommand(BMS, BQ40Z80_MFA_DA_STATUS_3, BMS_1.BQ_daStatus3, 18);
    BQ_ReadMABlockCommand(BMS, BQ40Z80_MFA_OUTPUT_CADC_CAL, BMS_1.BQ_outCal, 32);
    BQ_ParseAllFlags(BMS, operationStatus, batteryMode, batteryStatus, gpioStatus, manStatus, chargeStatus, gaugStatus);
}

/**
 * @brief update dastatus1, OperationStatus flags and ManufacturingStatus flags
 * @param none
 */
void BQAction_UpdateOpStatus(BQ_data* BMS)
{
    BQ_ReadMABlockCommand(BMS, BQ40Z80_MFA_DA_STATUS_1, BMS_1.BQ_daStatus1, 32);
    BQ_ParseOperationStatus(BMS, BQ_ReadCommandAsLInt(BMS, BQ40Z80_MFA_OPERATION_STATUS));
    BQ_ParseManufacturingStatus(BMS, BQ_ReadCommandAsShort(BMS, BQ40Z80_MFA_MANUFACTURING_STATUS));
}

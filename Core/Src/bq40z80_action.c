#include "bq40z80_action.h"
#include "bq40z80.h"

/**
 * @brief setting led
 * @param active true - set on, false - set off
 */
void BQAction_SetLed(bool active)
{
    if (BQ_IsLedEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_LED_TOGGLE);
    }
}

/**
 * @brief setting ManufacturingStatus()[FET_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingAllFet(bool active)
{
    if (BQ_IsManufacturingAllFetEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_FET_CONTROL);
    }
}

/**
 * @brief setting ManufacturingStatus()[FUSE_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingFuse(bool active)
{
    if (BQ_IsManufacturingFuseEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_FUSE);
    }
}
/**
 * @brief setting ManufacturingStatus()[CAL_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetCalibration(bool active)
{
    if (BQ_IsManufacturingCalibrationEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_CALIBRATION_MODE);
    }
}

/**
 * @brief setting ManufacturingStatus()[GAUGE_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingGauging(bool active)
{
    if (BQ_IsManufacturingGaugingEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_GAUGING);
    }
}
/**
 * @brief setting ManufacturingStatus()[PF_EN]
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingPF(bool active)
{
    if (BQ_IsManufacturingPermanentFailureEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PERMANENT_FAILURE);
    }
}
/**
 * @brief setting ManufacturingStatus()[LF_EN] lifetime
 * @param active true - set on, false - set off
 */
void BQAction_SetManufacturingLF(bool active)
{
    if (BQ_IsManufacturingLifetimeEnabled() != active)
    {
        BQ_WriteMABlockCommand(BQ40Z80_MFA_LIFETIME_DATA_COLLECTION);
    }
}

/**
 * @brief enable charge fet and disable the rest
 * @param none
 */
bool BQAction_EnableCharging(void)
{
    if (BQ_GetChargeMode() == CHARGE){
        return false;
    }

    // turn off unused fets
    if (BQ_IsDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BQ_IsPreDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }
    if (BQ_IsPreChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on charge
    if (!BQ_IsChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_CHG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode() == CHARGE){
        return true;
    }else{
        // turn off charge
        if (BQ_IsChargeFetTestEnabled()){
            BQ_WriteMABlockCommand(BQ40Z80_MFA_CHG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief enable discharge fet and disable the rest
 * @param none
 */
bool BQAction_EnableDischarging(void)
{
    if (BQ_GetChargeMode() == DISCHARGE){
        return false;
    }

    // turn off unused fets
    if (BQ_IsChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BQ_IsPreDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }
    if (BQ_IsPreChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on discharge
    if (!BQ_IsDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_DSG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode() != CHARGE){
        return true;
    }else{
        // turn off discharge
        if (BQ_IsDischargeFetTestEnabled()){
            BQ_WriteMABlockCommand(BQ40Z80_MFA_DSG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief enable predischarge fet and disable the rest
 * @param none
 */
bool BQAction_EnablePreDischarging(void)
{
    if (BQ_GetChargeMode() == DISCHARGE){
        return false;
    }

    // turn off unused fets
    if (BQ_IsChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BQ_IsDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BQ_IsPreChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }

    // turn on pre-discharge
    if (!BQ_IsPreDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }

    HAL_Delay(1500);

    if (BQ_GetChargeMode() != CHARGE){
        return true;
    }
    else
    {
        // turn off pre-discharge
        if (BQ_IsPreDischargeFetTestEnabled()){
            BQ_WriteMABlockCommand(BQ40Z80_MFA_PDSG_FET_TOGGLE);
        }
        return false;
    }
}

/**
 * @brief disable all fets
 * @param none
 */
bool BQAction_DisableFets(void)
{
    BQAction_UpdateOpStatus();
    if (BQ_IsChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_CHG_FET_TOGGLE);
    }
    if (BQ_IsDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_DSG_FET_TOGGLE);
    }
    if (BQ_IsPreChargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PCHG_FET_TOGGLE);
    }
    if (BQ_IsPreDischargeFetTestEnabled()){
        BQ_WriteMABlockCommand(BQ40Z80_MFA_PDSG_FET_TOGGLE);
    }

    return true;
}

/**
 * @brief trying to update flash registers
 * @param none
 * @return true - updated, false - not updated
 */
bool BQAction_TryUpdateFlash(void)
{
    return false;
}

/**
 * @brief force updating flash registers
 * @param none
 */
void BQAction_ForceUpdateFlash(void)
{
    FlashData *flashHex2 = BQ_GetFlashHex2();
    for (int i = 0; i < 45; i++)
    {
        BQ_WriteFlash(flashHex2[i].Address, flashHex2[i].Data);
        HAL_Delay(200);
    }

    FlashData *flashHex1 = BQ_GetFlashHex1();
    for (int i = 0; i < 12; i++)
    {
        BQ_WriteFlash(flashHex1[i].Address, flashHex1[i].Data);
        HAL_Delay(200);
    }
}

/**
 * @brief change sealed mode to unsealed
 * @param none
 **/
void BQAction_TryUnsealedDevice(void)
{
//    bool isSealed = false;

    BQAction_UpdateOpStatus();
    SECURITY_MODE securityMode = BQ_GetSecurityMode();
    while (securityMode == SEALED || securityMode == RESERVED)
    {
//        isSealed = true;
//        ("[BQ] Security mode - Sealed", 27);

        BQ_WriteMABlockCommand(0x0414);
        HAL_Delay(500);
        BQ_WriteMABlockCommand(0x3672);
        HAL_Delay(3000);

        BQAction_UpdateOpStatus();
        securityMode = BQ_GetSecurityMode();
    }

    // print only if the device was previously sealeded
//    if (isSealed){
//        ("[BQ] successfully unsealed", 27);
//    }

}

/**
 * @brief updating statuses, flags
 * @param none
 */
void BQAction_UpdateData(void)
{
    uint16_t manStatus = BQ_ReadCommandAsShort(BQ40Z80_MFA_MANUFACTURING_STATUS);
    uint32_t chargeStatus = BQ_ReadCommandAsInt(BQ40Z80_MFA_CHARGING_STATUS);
    uint32_t operationStatus = BQ_ReadCommandAsInt(BQ40Z80_MFA_OPERATION_STATUS);
    uint32_t gaugStatus = BQ_ReadCommandAsInt(BQ40Z80_MFA_GAUGING_STATUS);

    uint16_t batteryMode = I2CHelper_ReadRegisterAsShort(bq_i2c, bq_deviceAddress, BQ40Z80_SBS_BatteryMode);
    uint16_t batteryStatus = I2CHelper_ReadRegisterAsShort(bq_i2c, bq_deviceAddress, BQ40Z80_SBS_BatteryStatus);
    uint8_t gpioStatus = I2CHelper_ReadRegisterAsChar(bq_i2c, bq_deviceAddress, BQ40Z80_SBS_GPIORead);

    BQ_ReadMABlockCommand(BQ40Z80_MFA_DA_STATUS_1, BQ_daStatus1, 32);
    BQ_ReadMABlockCommand(BQ40Z80_MFA_DA_STATUS_2, BQ_daStatus2, 16);
    BQ_ReadMABlockCommand(BQ40Z80_MFA_DA_STATUS_3, BQ_daStatus3, 18);
    BQ_ReadMABlockCommand(BQ40Z80_MFA_OUTPUT_CADC_CAL, BQ_outCal, 32);
    BQ_ParseAllFlags(operationStatus, batteryMode, batteryStatus, gpioStatus, manStatus, chargeStatus, gaugStatus);
}

/**
 * @brief update dastatus1, OperationStatus flags and ManufacturingStatus flags
 * @param none
 */
void BQAction_UpdateOpStatus(void)
{
    BQ_ReadMABlockCommand(BQ40Z80_MFA_DA_STATUS_1, BQ_daStatus1, 32);
    BQ_ParseOperationStatus(BQ_ReadCommandAsInt(BQ40Z80_MFA_OPERATION_STATUS));
    BQ_ParseManufacturingStatus(BQ_ReadCommandAsShort(BQ40Z80_MFA_MANUFACTURING_STATUS));
}

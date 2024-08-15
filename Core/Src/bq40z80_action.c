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
        BQ_WriteMABlockCommand(CMD_LED_TOGGLE);
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
        BQ_WriteMABlockCommand(CMD_ALL_FET_EN);
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
        BQ_WriteMABlockCommand(CMD_MAN_FUSE);
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
        BQ_WriteMABlockCommand(CMD_CALIBRATION);
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
        BQ_WriteMABlockCommand(CMD_GAUGING);
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
        BQ_WriteMABlockCommand(CMD_PF_EN);
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
        BQ_WriteMABlockCommand(CMD_LF_EN);
    }
}

/**
 * @brief enable charge fet and disable the rest
 * @param none
 */
bool BQAction_EnableCharging(void)
{
    if (BQ_GetChargeMode() == CHARGE)
        return false;

    // turn off unused fets
    if (BQ_IsDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_DSG);
    if (BQ_IsPreDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PDSG);
    if (BQ_IsPreChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PCHG);

    // turn on charge
    if (!BQ_IsChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_CHG);

    HAL_Delay(1500);

    if (BQ_GetChargeMode() == CHARGE)
        return true;
    else
    {
        // turn off charge
        if (BQ_IsChargeFetTestEnabled())
            BQ_WriteMABlockCommand(CMD_FET_CHG);
        return false;
    }
}

/**
 * @brief enable discharge fet and disable the rest
 * @param none
 */
bool BQAction_EnableDischarging(void)
{
    if (BQ_GetChargeMode() == DISCHARGE)
        return false;

    // turn off unused fets
    if (BQ_IsChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_CHG);
    if (BQ_IsPreDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PDSG);
    if (BQ_IsPreChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PCHG);

    // turn on discharge
    if (!BQ_IsDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_DSG);

    HAL_Delay(1500);

    if (BQ_GetChargeMode() != CHARGE)
        return true;
    else
    {
        // turn off discharge
        if (BQ_IsDischargeFetTestEnabled())
            BQ_WriteMABlockCommand(CMD_FET_DSG);
        return false;
    }
}

/**
 * @brief enable predischarge fet and disable the rest
 * @param none
 */
bool BQAction_EnablePreDischarging(void)
{
    if (BQ_GetChargeMode() == DISCHARGE)
        return false;

    // turn off unused fets
    if (BQ_IsChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_CHG);
    if (BQ_IsDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_DSG);
    if (BQ_IsPreChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PCHG);

    // turn on pre-discharge
    if (!BQ_IsPreDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PDSG);

    HAL_Delay(1500);

    if (BQ_GetChargeMode() != CHARGE)
        return true;
    else
    {
        // turn off pre-discharge
        if (BQ_IsPreDischargeFetTestEnabled())
            BQ_WriteMABlockCommand(CMD_FET_PDSG);
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
    if (BQ_IsChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_CHG);
    if (BQ_IsDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_DSG);
    if (BQ_IsPreChargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PCHG);
    if (BQ_IsPreDischargeFetTestEnabled())
        BQ_WriteMABlockCommand(CMD_FET_PDSG);

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
    bool isSealed = false;

    BQAction_UpdateOpStatus();
    SECURITY_MODE securityMode = BQ_GetSecurityMode();
    while (securityMode == SEALED || securityMode == RESERVED)
    {
        isSealed = true;
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
    unsigned short manStatus = BQ_ReadCommandAsShort(0x0057);
    unsigned int chargeStatus = BQ_ReadCommandAsInt(0x0055);
    unsigned int operationStatus = BQ_ReadCommandAsInt(0x0054);
    unsigned int gaugStatus = BQ_ReadCommandAsInt(0x0056);

    unsigned short batteryMode = I2CHelper_ReadRegisterAsShort(bq_i2c, bq_deviceAddress, REG_BATTERY_MODE);
    unsigned short batteryStatus = I2CHelper_ReadRegisterAsShort(bq_i2c, bq_deviceAddress, REG_BATTERY_STATUS);
    unsigned char gpioStatus = I2CHelper_ReadRegisterAsChar(bq_i2c, bq_deviceAddress, REG_GPIO_READ);

    BQ_ReadMABlockCommand(0x0071, BQ_daStatus1, 32);
    BQ_ReadMABlockCommand(0x0072, BQ_daStatus2, 16);
    BQ_ReadMABlockCommand(0x007B, BQ_daStatus3, 18);
    BQ_ReadMABlockCommand(0xF081, BQ_outCal, 32);
    BQ_ParseAllFlags(operationStatus, batteryMode, batteryStatus, gpioStatus, manStatus, chargeStatus, gaugStatus);
}

/**
 * @brief update dastatus1, OperationStatus flags and ManufacturingStatus flags
 * @param none
 */
void BQAction_UpdateOpStatus(void)
{
    BQ_ReadMABlockCommand(0x0071, BQ_daStatus1, 32);
    BQ_ParseOperationStatus(BQ_ReadCommandAsInt(0x0054));
    BQ_ParseManufacturingStatus(BQ_ReadCommandAsShort(0x0057));
}

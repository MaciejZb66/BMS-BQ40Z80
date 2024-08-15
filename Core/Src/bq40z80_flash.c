#include "bq40z80_flash.h"

/**
 * @brief function with stored pairs (key, hex2value) for flash
 * @param none
 * @return FlashData array
 */
FlashData *BQ_GetFlashHex2(void)
{
    static FlashData flashHex2[45] = {
        // settings
        {0x4AC7, 0x017D}, // FET Options
        {0x4ACC, 0x0330}, // Power Config
        {0x4AD3, 0x77E4}, // Pin Configuration
        {0x4B0C, 0x01D7}, // Led Configuration
        {0x4D03, 0x001A}, // DA Configuration
        {0x4800, 0x0228}, // Mfg Status init
        // protections
        {0x4BC2, 2600}, // CUV Threshold
        {0x4BC5, 2700}, // CUV Recovery
        {0x4BC7, 2600}, // CUVC Threshold
        {0x4BCA, 2700}, // CUVC Recovery
        {0x4BD7, 4000}, // COV Recovery Low Temp
        {0x4BD9, 4000}, // COV Recovery Standard Temp Low
        {0x4BDB, 4000}, // COV Recovery Standard Temp High
        {0x4BDD, 4000}, // COV Recovery High Temp
        {0x4BDF, 4000}, // COV Recovery Rec Temp
        {0x4BCC, 4000}, // COV Threshold Low Temp
        {0x4BCE, 4000}, // COV Threshold Standard Temp Low
        {0x4BD0, 4000}, // COV Threshold Standard Temp High
        {0x4BD2, 4000}, // COV Threshold High Temp
        {0x4BD4, 4000}, // COV Threshold Rec Temp
        // design
        {0x4B69, 5400},  // Design Capacity mAh
        {0x4B6D, 24600}, // Design Voltage
        // gauging
        {0x4B7A, 4100}, // FC Set Voltage Threshold
        {0x4B7C, 4000}, // FC Clear Voltage Threshold
        {0x4B74, 2600}, // FD Set Voltage Threshold
        {0x4B76, 2700}, // FD Clear Voltage Threshold
        {0x4B86, 4100}, // TC Set Voltage Threshold
        {0x4B88, 4000}, // TC Clear Voltage Threshold
        {0x4B80, 2800}, // TD Set Voltage Threshold
        {0x4B82, 2900}, // TD Clear Voltage Threshold
        {0x44C6, 5400}, // Qmax Cell 1
        {0x44C8, 5400}, // Qmax Cell 2
        {0x44CA, 5400}, // Qmax Cell 3
        {0x44CC, 5400}, // Qmax Cell 4
        {0x44CE, 5400}, // Qmax Cell 5
        {0x44D0, 5400}, // Qmax Cell 6
        {0x44D2, 5400}, // Qmax Cell 7
        {0x44D4, 5400}, // Qmax Pack
        {0x44D9, 4100}, // Cell 1 Chg Voltage at EoC
        {0x44DB, 4100}, // Cell 2 Chg Voltage at EoC
        {0x44DD, 4100}, // Cell 3 Chg Voltage at EoC
        {0x44DF, 4100}, // Cell 4 Chg Voltage at EoC
        {0x44E1, 4100}, // Cell 5 Chg Voltage at EoC
        {0x44E3, 4100}, // Cell 6 Chg Voltage at EoC
        {0x44E5, 4100}, // Cell 7 Chg Voltage at EoC
    };
    return flashHex2;
}

/**
 * @brief function with stored pairs (key, hex1value) for flash
 * @param none
 * @return FlashData array
 */
FlashData *BQ_GetFlashHex1(void)
{
    static FlashData flashHex1[12] = {
        {0x4AC9, 0x04}, // Sbs gauging Configuration
        {0x4ACA, 0x20}, // Sbs Configuration
        {0x4ACE, 0x20}, // IO Config
        {0x4B8C, 0x25}, // Balancing Configuration
        {0x4C90, 0x00}, // Charging Configuration
        {0x4D01, 0x06}, // Temperature enable
        {0x4D02, 0x04}, // Temperature mode
        // protections
        {0x4BBD, 0x0},  // Protection Configuration
        {0x4BBE, 0xFF}, // Enabled Protections A
        {0x4BBF, 0xFF}, // Enabled Protections B
        {0x4BC0, 0xFD}, // Enabled Protections C
        {0x4BC1, 0xFF}  // Enabled Protections D
    };

    return flashHex1;
}
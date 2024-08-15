#pragma once

#define BQ40Z80_MFA_DEVICE_TYPE 0x0001
#define BQ40Z80_MFA_FIRMWARE_VERSION 0x0002
#define BQ40Z80_MFA_HARDWARE_VERSION 0x0003
#define BQ40Z80_MFA_INSTRUCTION_FLASH_SIGNATURE 0x0004
#define BQ40Z80_MFA_STATIC_DF_SIGNATURE 0x0005
#define BQ40Z80_MFA_CHEMICAL_ID 0x0006
#define BQ40Z80_MFA_STATIC_CHEM_DF_SIGNATURE 0x0008
#define BQ40Z80_MFA_ALL_DF_SIGNATURE 0x0009
#define BQ40Z80_MFA_SHUTDOWN_MODE 0x0010
#define BQ40Z80_MFA_SLEEP_MODE 0x0011
#define BQ40Z80_MFA_AUTO_CC_OFFSET 0x0013
#define BQ40Z80_MFA_PDSG_FET_TOGGLE 0x001C
#define BQ40Z80_MFA_FUSE_TOGGLE 0x001D
#define BQ40Z80_MFA_PCHG_FET_TOGGLE 0x001E
#define BQ40Z80_MFA_CHG_FET_TOGGLE 0x001F
#define BQ40Z80_MFA_DSG_FET_TOGGLE 0x0020
#define BQ40Z80_MFA_GAUGING 0x0021
#define BQ40Z80_MFA_FET_CONTROL 0x0022
#define BQ40Z80_MFA_LIFETIME_DATA_COLLECTION 0x0023
#define BQ40Z80_MFA_PERMANENT_FAILURE 0x0024
#define BQ40Z80_MFA_BLACK_BOX_RECORDER 0x0025
#define BQ40Z80_MFA_FUSE 0x0026
#define BQ40Z80_MFA_LED_DISPLAY_ENABLE 0x0027
#define BQ40Z80_MFA_LIFETIME_DATA_RESET 0x0028
#define BQ40Z80_MFA_PERMANENT_FAIL_DATA_RESET 0x0029
#define BQ40Z80_MFA_BLACK_BOX_RECORDER_RESET 0x002A
#define BQ40Z80_MFA_LED_TOGGLE 0x002B
#define BQ40Z80_MFA_LED_DISPLAY_PRESS 0x002C
#define BQ40Z80_MFA_CALIBRATION_MODE 0x002D
#define BQ40Z80_MFA_LIFETIME_DATA_FLUSH 0x002E
#define BQ40Z80_MFA_LIFETIME_DATA_SPEED_UP_MODE 0x002F
#define BQ40Z80_MFA_SEAL_DEVICE 0x0030
#define BQ40Z80_MFA_SECURITY_KEYS 0x0035
#define BQ40Z80_MFA_AUTHENTICATION_KEY 0x0037
#define BQ40Z80_MFA_DEVICE_RESET 0x0041
#define BQ40Z80_MFA_SAFETY_ALERT 0x0050
#define BQ40Z80_MFA_SAFETY_STATUS 0x0051
#define BQ40Z80_MFA_PFALERT 0x0052
#define BQ40Z80_MFA_PFSTATUS 0x0053
#define BQ40Z80_MFA_OPERATION_STATUS 0x0054
#define BQ40Z80_MFA_CHARGING_STATUS 0x0055
#define BQ40Z80_MFA_GAUGING_STATUS 0x0056
#define BQ40Z80_MFA_MANUFACTURING_STATUS 0x0057
#define BQ40Z80_MFA_AFE_REGISTER 0x0058
#define BQ40Z80_MFA_NO_LOAD_REM_CAP 0x005A
#define BQ40Z80_MFA_LIFETIME_DATA_BLOCK_1 0x0060
#define BQ40Z80_MFA_LIFETIME_DATA_BLOCK_2 0x0061
#define BQ40Z80_MFA_LIFETIME_DATA_BLOCK_3 0x0062
#define BQ40Z80_MFA_LIFETIME_DATA_BLOCK_4 0x0063
#define BQ40Z80_MFA_LIFETIME_DATA_BLOCK_5 0x0064
#define BQ40Z80_MFA_MANUFACTURER_INFO 0x0070
#define BQ40Z80_MFA_DA_STATUS_1 0x0071
#define BQ40Z80_MFA_DA_STATUS_2 0x0072
#define BQ40Z80_MFA_GAUGING_STATUS_1 0x0073
#define BQ40Z80_MFA_GAUGING_STATUS_2 0x0074
#define BQ40Z80_MFA_GAUGING_STATUS_3 0x0075
#define BQ40Z80_MFA_CB_STATUS 0x0076
#define BQ40Z80_MFA_STATE_OF_HEALTH 0x0077
#define BQ40Z80_MFA_FILTER_CAPACITY 0x0078
#define BQ40Z80_MFA_RSOC_WRITE 0x0079
#define BQ40Z80_MFA_MANUFACTURER_INFO_B 0x007A
#define BQ40Z80_MFA_DA_STATUS_3 0x007B
#define BQ40Z80_MFA_GAUGING_STATUS_4 0x007C
#define BQ40Z80_MFA_GAUGING_STATUS_5 0x007D
#define BQ40Z80_MFA_MANUFACTURER_INFO_C 0x0080
#define BQ40Z80_MFA_MANUFACTURER_INFO_D 0x0081
#define BQ40Z80_MFA_CURRENT_LONG 0x0082
#define BQ40Z80_MFA_IATA_SHUTDOWN 0x00F0
#define BQ40Z80_MFA_IATA_RM 0x00F1
#define BQ40Z80_MFA_IATA_FCC 0x00F2
#define BQ40Z80_MFA_IATA_CHARGE 0x00F3
#define BQ40Z80_MFA_ROM_MODE 0x0F00
#define BQ40Z80_MFA_WRITE_TEMP 0x3008
//--------------0x4000 - 0x5FFF------------------
//-----------------------------------------------
#define BQ40Z80_MFA_EXIT_CALIBRATION_OUTPUT_MODE 0xF080
#define BQ40Z80_MFA_OUTPUT_CADC_CAL 0xF081
#define BQ40Z80_MFA_OUTPUT_SHORTEDCCADCCAL 0xF082
#define BQ40Z80_MFA_OUTPUT_CCADC_CAL 0xF083

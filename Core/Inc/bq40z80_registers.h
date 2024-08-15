#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t cell_voltage_1; //!< Cell Voltage 1 (mV)
    uint16_t cell_voltage_2; //!< Cell Voltage 2 (mV)
    uint16_t cell_voltage_3; //!< Cell Voltage 3 (mV)
    uint16_t cell_voltage_4; //!< Cell Voltage 4 (mV)
    uint16_t bat_voltage;    //!< BAT Voltage. Voltage at the BAT pin. Different from Voltage() which is the sum of all cell voltages (mV)
    uint16_t pack_voltage;   //!< PACK Voltage. Voltage at the PACK+ pin. (mV)
    uint16_t cell_current_1; //!< Cell Current 1. Simultaneous current measured during Cell Voltage 1 measurement (mA)
    uint16_t cell_current_2; //!< Cell Current 2. Simultaneous current measured during Cell Voltage 2 measurement (mA)
    uint16_t cell_current_3; //!< Cell Current 3. Simultaneous current measured during Cell Voltage 3 measurement (mA)
    uint16_t cell_current_4; //!< Cell Current 4. Simultaneous current measured during Cell Voltage 4 measurement (mA)
    uint16_t cell_power_1;   //!< Cell Power 1. Calculated using Cell Voltage1 and Cell Current 1 data (cW)
    uint16_t cell_power_2;   //!< Cell Power 2. Calculated using Cell Voltage2 and Cell Current 2 data (cW)
    uint16_t cell_power_3;   //!< Cell Power 3. Calculated using Cell Voltage3 and Cell Current 3 data (cW)
    uint16_t cell_power_4;   //!< Cell Power 4. Calculated using Cell Voltage4 and Cell Current 4 data (cW)
    uint16_t power;          //!< Power calculated by Voltage() × Current() (cW)
    uint16_t average_power;  //!< Average Power (cW)
} DA_STATUS_1; //0x0071

typedef struct
{
    uint16_t int_temperature;     //!< Int Temperature (0.1 K)
    uint16_t ts1_temperature;     //!< TS1 Temperature (0.1 K)
    uint16_t ts2_temperature;     //!< TS2 Temperature (0.1 K)
    uint16_t ts3_temperature;     //!< TS3 Temperature (0.1 K)
    uint16_t ts4_temperature;     //!< TS4 Temperature (0.1 K)
    uint16_t cell_temperature;    //!< Cell Temperature (0.1 K)
    uint16_t fet_temperature;     //!< FET Temperature (0.1 K)
    uint16_t gauging_temperature; //!< Gauging Temperature (0.1 K)
} DA_STATUS_2; //0x0072

typedef struct
{
    uint16_t cell_voltage_5; //!< Cell Voltage 5 (mV)
    uint16_t cell_voltage_6; //!< Cell Voltage 6 (mV)
    uint16_t cell_voltage_7; //!< Cell Voltage 7 (mV)
    uint16_t cell_current_5; //!< Cell Current 5. Simultaneous current measured during Cell Voltage 5 measurement (mA)
    uint16_t cell_current_6; //!< Cell Current 6. Simultaneous current measured during Cell Voltage 6 measurement (mA)
    uint16_t cell_current_7; //!< Cell Current 7. (mA)
    uint16_t cell_power_5;   //!< Cell Power 5. Calculated using Cell Voltage 5 and Cell Current 5 data (cW)
    uint16_t cell_power_6;   //!< Cell Power 6. Calculated using Cell Voltage 6 and Cell Current 6 data (cW)
    uint16_t cell_power_7;   //!< Cell Power 7. Calculated using Cell Voltage 7 and Cell Current 7 data (cW)
} DA_STATUS_3; //0x007B

typedef struct
{
    uint32_t iata_cterm :1; //!< IATA charge control: 1 = Active, 0 = Inactive
    uint32_t rsvd_30 :1;    //!< Reserved. Do not use.
    uint32_t emshut :1;     //!< Emergency FET shutdown: 1 = Active, 0 = Inactive
    uint32_t cb :1;         //!< Cell balancing status: 1 = Active, 0 = Inactive
    uint32_t slpcc :1;      //!< CC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    uint32_t slpad :1;      //!< ADC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    uint32_t smblcal :1;    //!< Auto CC calibration
    uint32_t init :1;       //!< Initialization after full reset: 1 = Active, 0 = Inactive
    uint32_t sleepm :1;     //!< SLEEP mode triggered via command: 1 = Active, 0 = Inactive
    uint32_t xl :1;         //!< 400-kHz SMBus mode: 1 = Active, 0 = Inactive
    uint32_t cal_offset :1; //!< Calibration output (raw CC offset data)
    uint32_t cal :1;        //!< Calibration output (raw ADC and CC data)
    uint32_t autocalm :1;   //!< Auto CC Offset calibration by the MAC AutoCCOffset(): 1 = Calibration ongoing, 0 = Calibration completed
    uint32_t auth :1;       //!< Authentication in progress: 1 = Active, 0 = Inactive
    uint32_t led :1;        //!< LED Display: 1 = Display on, 0 = Display off
    uint32_t sdm :1;        //!< Shutdown triggered via command: 1 = Active, 0 = Inactive
    uint32_t sleep :1;      //!< SLEEP mode conditions met: 1 = Active, 0 = Inactive
    uint32_t xchg :1;       //!< Charging disabled: 1 = Active, 0 = Inactive
    uint32_t xdsg :1;       //!< Discharging disabled: 1 = Active, 0 = Inactive
    uint32_t pf :1;         //!< PERMANENT FAILURE mode status: 1 = Active, 0 = Inactive
    uint32_t ss :1;         //!< SAFETY status: 1 = Active, 0 = Inactive
    uint32_t sdv :1;        //!< Shutdown triggered via low battery stack voltage: 1 = Active, 0 = Inactive
    uint32_t sec1 :1;       //!< SECURITY mode bit 1
    uint32_t sec0 :1;       //!< SECURITY mode bit 0
    uint32_t btp_int :1;    //!< Battery trip point interrupt: 1 = Active, 0 = Inactive
    uint32_t rsvd_6 :1;     //!< Reserved. Do not use.
    uint32_t fuse :1;       //!< Fuse status: 1 = Active, 0 = Inactive
    uint32_t pdsg :1;       //!< Pre-discharge FET status: 1 = Active, 0 = Inactive
    uint32_t pchg :1;       //!< Precharge FET status: 1 = Active, 0 = Inactive
    uint32_t chg :1;        //!< CHG FET status: 1 = Active, 0 = Inactive
    uint32_t dsg :1;        //!< DSG FET status: 1 = Active, 0 = Inactive
    uint32_t pres :1;       //!< System present low: 1 = Active, 0 = Inactive
} OPERATION_STATUS; //0x0054

typedef struct
{
    // Charging Status Flags (Bits 23–8)
    bool rsvd_23; //!< Reserved. Do not use.
    bool rsvd_22; //!< Reserved. Do not use.
    bool rsvd_21; //!< Reserved. Do not use.
    bool rsvd_20; //!< Reserved. Do not use.
    bool nct;     //!< Near charge termination: 1 = Active, 0 = Inactive
    bool ccc;     //!< Charging loss compensation: 1 = Active, 0 = Inactive
    bool cvr;     //!< Charging voltage rate of change: 1 = Active, 0 = Inactive
    bool ccr;     //!< Charging current rate of change: 1 = Active, 0 = Inactive
    bool vct;     //!< Charge termination: 1 = Active, 0 = Inactive
    bool mchg;    //!< Maintenance charge: 1 = Active, 0 = Inactive
    bool su;      //!< Suspend charge: 1 = Active, 0 = Inactive
    bool in;      //!< Charge inhibit: 1 = Active, 0 = Inactive
    bool hv;      //!< High voltage region: 1 = Active, 0 = Inactive
    bool mv;      //!< Mid voltage region: 1 = Active, 0 = Inactive
    bool lv;      //!< Low voltage region: 1 = Active, 0 = Inactive
    bool pv;      //!< Precharge voltage region: 1 = Active, 0 = Inactive

    // Temperature Range Flags (Bits 7–0)
    bool rsvd_7; //!< Reserved. Do not use.
    bool ot;     //!< Overtemperature region: 1 = Active, 0 = Inactive
    bool ht;     //!< High temperature region: 1 = Active, 0 = Inactive
    bool sth;    //!< Standard temperature high region: 1 = Active, 0 = Inactive
    bool rt;     //!< Recommended temperature region: 1 = Active, 0 = Inactive
    bool stl;    //!< Standard temperature low region: 1 = Active, 0 = Inactive
    bool lt;     //!< Low temperature region: 1 = Active, 0 = Inactive
    bool ut;     //!< Undertemperature region: 1 = Active, 0 = Inactive
} CHARGING_STATUS; //0x0055

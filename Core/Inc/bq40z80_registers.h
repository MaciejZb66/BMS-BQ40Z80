#pragma once
#include <stdint.h>

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
    uint32_t iata_cterm :1; //!<31 IATA charge control: 1 = Active, 0 = Inactive
    uint32_t rsvd_30 :1;    //!<30 Reserved. Do not use.
    uint32_t emshut :1;     //!<29 Emergency FET shutdown: 1 = Active, 0 = Inactive
    uint32_t cb :1;         //!<28 Cell balancing status: 1 = Active, 0 = Inactive
    uint32_t slpcc :1;      //!<27 CC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    uint32_t slpad :1;      //!<26 ADC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    uint32_t smblcal :1;    //!<25 Auto CC calibration
    uint32_t init :1;       //!<24 Initialization after full reset: 1 = Active, 0 = Inactive

    uint32_t sleepm :1;     //!<23 SLEEP mode triggered via command: 1 = Active, 0 = Inactive
    uint32_t xl :1;         //!<22 400-kHz SMBus mode: 1 = Active, 0 = Inactive
    uint32_t cal_offset :1; //!<21 Calibration output (raw CC offset data)
    uint32_t cal :1;        //!<20 Calibration output (raw ADC and CC data)
    uint32_t autocalm :1;   //!<19 Auto CC Offset calibration by the MAC AutoCCOffset(): 1 = Calibration ongoing, 0 = Calibration completed
    uint32_t auth :1;       //!<18 Authentication in progress: 1 = Active, 0 = Inactive
    uint32_t led :1;        //!<17 LED Display: 1 = Display on, 0 = Display off
    uint32_t sdm :1;        //!<16 Shutdown triggered via command: 1 = Active, 0 = Inactive

    uint32_t sleep :1;      //!<15 SLEEP mode conditions met: 1 = Active, 0 = Inactive
    uint32_t xchg :1;       //!<14 Charging disabled: 1 = Active, 0 = Inactive
    uint32_t xdsg :1;       //!<13 Discharging disabled: 1 = Active, 0 = Inactive
    uint32_t pf :1;         //!<12 PERMANENT FAILURE mode status: 1 = Active, 0 = Inactive
    uint32_t ss :1;         //!<11 SAFETY status: 1 = Active, 0 = Inactive
    uint32_t sdv :1;        //!<10 Shutdown triggered via low battery stack voltage: 1 = Active, 0 = Inactive
    uint32_t sec1 :1;       //!<9 SECURITY mode bit 1
    uint32_t sec0 :1;		//!<8 SECURITY mode bit 0

    uint32_t btp_int :1;    //!<7 Battery trip point interrupt: 1 = Active, 0 = Inactive
    uint32_t rsvd_6 :1;     //!<6 Reserved. Do not use.
    uint32_t fuse :1;       //!<5 Fuse status: 1 = Active, 0 = Inactive
    uint32_t pdsg :1;       //!<4 Pre-discharge FET status: 1 = Active, 0 = Inactive
    uint32_t pchg :1;       //!<3 Precharge FET status: 1 = Active, 0 = Inactive
    uint32_t chg :1;        //!<2 CHG FET status: 1 = Active, 0 = Inactive
    uint32_t dsg :1;        //!<1 DSG FET status: 1 = Active, 0 = Inactive
    uint32_t pres :1;       //!<0 System present low: 1 = Active, 0 = Inactive
} OPERATION_STATUS; //0x0054

typedef struct
{
	uint32_t unused :8;
    // Charging Status Flags (Bits 23–8)
    uint32_t rsvd_2320 :4; 	//!<23-20 Reserved. Do not use.
    uint32_t nct :1;     	//!<19 Near charge termination: 1 = Active, 0 = Inactive
    uint32_t ccc :1;     	//!<18 Charging loss compensation: 1 = Active, 0 = Inactive
    uint32_t cvr :1;     	//!<17 Charging voltage rate of change: 1 = Active, 0 = Inactive
    uint32_t ccr :1;     	//!<16 Charging current rate of change: 1 = Active, 0 = Inactive

    uint32_t vct :1;     	//!<15 Charge termination: 1 = Active, 0 = Inactive
    uint32_t mchg :1;    	//!<14 Maintenance charge: 1 = Active, 0 = Inactive
    uint32_t su :1;      	//!<13 Suspend charge: 1 = Active, 0 = Inactive
    uint32_t in :1;      	//!<12 Charge inhibit: 1 = Active, 0 = Inactive
    uint32_t hv :1;      	//!<11 High voltage region: 1 = Active, 0 = Inactive
    uint32_t mv :1;      	//!<10 Mid voltage region: 1 = Active, 0 = Inactive
    uint32_t lv :1;      	//!<9 Low voltage region: 1 = Active, 0 = Inactive
    uint32_t pv :1;      	//!<8 Precharge voltage region: 1 = Active, 0 = Inactive

    // Temperature Range Flags (Bits 7–0)
    uint32_t rsvd_7 :1; 	//!<7 Reserved. Do not use.
    uint32_t ot :1;     	//!<6 Overtemperature region: 1 = Active, 0 = Inactive
    uint32_t ht :1;     	//!<5 High temperature region: 1 = Active, 0 = Inactive
    uint32_t sth :1;    	//!<4 Standard temperature high region: 1 = Active, 0 = Inactive
    uint32_t rt :1;    		//!<3 Recommended temperature region: 1 = Active, 0 = Inactive
    uint32_t stl :1;    	//!<2 Standard temperature low region: 1 = Active, 0 = Inactive
    uint32_t lt :1;     	//!<1 Low temperature region: 1 = Active, 0 = Inactive
    uint32_t ut :1;     	//!<0 Undertemperature region: 1 = Active, 0 = Inactive
} CHARGING_STATUS; //0x0055

typedef struct{
	uint32_t unused :8;

	uint32_t rsvd_2321 :3;	//!<23-21 Reserved. Do not use.
	uint32_t ocv :1;		//!<20 Open circut voltage in flat region
	uint32_t ldmd :1;		//!<19 Load more
	uint32_t rx :1;			//!<18 Resistant update
	uint32_t qmax :1;		//!<17 Qmax update
	uint32_t vdq :1;		//!<16 Dicharge qualified for learning

	uint32_t nsfm :1;		//!<15 Negative scale factor mode
	uint32_t rsvd_14 :1;	//!<14 Reserved. Do not use.
	uint32_t slp :1;		//!<13 OCV update in sleep mode
	uint32_t qen :1;		//!<12 Impedance track gauging
	uint32_t vok :1;		//!<11 Voltages are ok for qmax update
	uint32_t r_dis :1;		//!<10 Resistance updates
	uint32_t rsvd_9 :1;		//!<9 Reserved. Do not use.
	uint32_t rest :1;		//!<8 Rest

	uint32_t cf :1;			//!<7 Condition flag
	uint32_t dsg :1;		//!<6 Dicharge/relax
	uint32_t edv :1;		//!<5 End of discharge termination voltage
	uint32_t bal_en :1;		//!<4 Cell balancing
	uint32_t tc :1;			//!<3 Terminate charge
	uint32_t td :1;			//!<2 Terminate discharge
	uint32_t fc :1;			//!<1 Fully charged
	uint32_t fd :1;			//!<0 Fully discharged
}GAUGING_STATUS;//0x0056

typedef struct{
	uint16_t cal :1;		//!<15 Calibration mode: 1 = Active, 0 = Inactive
	uint16_t lft :1; 		//!<14 Lifetime speed up: 1 = Active, 0 = Inactive
	uint16_t pdsg :1;		//!<13 Pre-discharge fet test: 1 = Active, 0 = Inactive
	uint16_t rsvd_1210 :3; 	//!<12-10 Reserved. Do not use.
	uint16_t led :1;		//!<9 Led display when button is pressed
	uint16_t fuse :1;		//!<8 Fuse action: 1 = Active, 0 = Inactive

	uint16_t bbr :1;		//!<7 Black box recorder: 1 = Active, 0 = Inactive
	uint16_t pf :1;			//!<6 Permanent failure: 1 = Active, 0 = Inactive
	uint16_t lf :1;			//!<5 Lifetime data collection: 1 = Active, 0 = Inactive
	uint16_t fet :1;		//!<4 All FET action: 1 = Active, 0 = Inactive
	uint16_t gauge :1;		//!<3 Gas gauging: 1 = Active, 0 = Inactive
	uint16_t dsg :1;		//!<2 Discharge fet test: 1 = Active, 0 = Inactive
	uint16_t chg :1;		//!<1 Charge fet test: 1 = Active, 0 = Inactive
	uint16_t pchg :1;		//!<0 Precharge fet test: 1 = Active, 0 = Inactive
}MANUFACTURING_STATUS;//0x0057

typedef struct{
	uint16_t camp :1;		//!<15 Capacity mode
	uint16_t chgm :1;		//!<14 Charger mode
	uint16_t am :1;			//!<13 Alarm mode
	uint16_t rsvd :3;		//!<12-10 Reserved. Do not use.
	uint16_t pb :1;			//!<9 Primary battery
	uint16_t cc :1;			//!<8 Charge controler enabled

	uint16_t cf :1;			//!<7 Condition flag
	uint16_t rsvd_62 :5;	//!<6-2 Reserved. Do not use.
	uint16_t pbs :1;		//!<1 Primary battery support
	uint16_t icc :1;		//!<0 Internal charge controler
}BATTERY_MODE;//0x03

typedef struct{
	uint16_t oca :1;		//!<15 Overcharged alarm
	uint16_t tca :1;		//!<14 terminate charge alarm
	uint16_t rsvd_13 :1;	//!<13 Reserved. Do not use.
	uint16_t ota :1;		//!<12 Overtemperature alarm
	uint16_t tda :1;		//!<11 Terminate discharge alarm
	uint16_t rsvd_10 :1;	//!<10 Reserved. Do not use.
	uint16_t rca :1;		//!<9 Remaining capacity alarm
	uint16_t rta :1;		//!<8 Remaining time alarm

	uint16_t init :1;		//!<7 Initialization
	uint16_t dsg :1;		//!<6 Discharge or relax
	uint16_t fc :1;			//!<5 Fully charged
	uint16_t fd :1;			//!<4 Fully discharged
	uint16_t err :4;		//!<3-0 Error code
}BATTERY_STATUS;//0x16



#include "bq40z80_parser.h"
#include "bq40z80_mfa.h"
#include "bq40z80_sbs.h"
#include "bq40z80_registers.h"
#include "bq40z80_validator.h"
#include "bq40z80_flash.h"
#include "bq40z80_action.h"
#include "bq40z80_data.h"
#include "i2c_helper.h"
#include "i2c.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

#define USE_SCANNER // 1 //test if ready

//#define REG_TEMPERATURE 0x08
//#define REG_VOLTAGE 0x09 // input voltage
//#define REG_RELATIVE_STATE_CHARGE 0x0D
//#define REG_ABSOLUTE_STATE_CHARGE 0x0E
//#define REG_FULL_CHARGE_CAPACITY 0x10
//#define REG_GPIO_WRITE 0x49
//#define REG_GPIO_READ 0x48
//#define REG_BATTERY_MODE 0x03
//#define REG_BATTERY_STATUS 0x16
//#define REG_CYCLE_COUNT 0x17
//#define REG_OPERATION_STATUS 0x54
//#define REG_PF_STATUS 0x53
//#define REG_SAFETY_STATUS 0x51
//#define REG_CHARGING_STATUS 0x55
//#define REG_GAUGING_STATUS 0x56
//#define REG_MANAFACTURING_STATUS 0x57P

extern uint8_t bq_deviceAddress;

void BQ_Init(I2C_HandleTypeDef *i2c);

void BQ_WriteMABlockCommand(BQ_data BMS,uint16_t command);
void BQ_ReadMABlockCommand(BQ_data BMS, uint16_t command, uint8_t *receive, uint8_t size);

uint16_t BQ_ReadCommandAsShort(BQ_data BMS, uint16_t command);
uint32_t BQ_ReadCommandAsInt(BQ_data BMS, uint16_t command);
uint8_t BQ_ReadCommandAsChar(BQ_data BMS, uint16_t command);
uint32_t BQ_ReadCommandAsLInt(BQ_data BMS, uint16_t command);

void BQ_WriteFlash(BQ_data BMS, uint16_t addr, uint16_t writeData);
void BQ_WriteFlashByte(BQ_data BMS, uint16_t addr, uint8_t writeData);

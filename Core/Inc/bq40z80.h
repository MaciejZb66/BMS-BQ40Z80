
#include "bq40z80_parser.h"
#include "bq40z80_mfa.h"
#include "bq40z80_sbs.h"
#include "bq40z80_registers.h"
#include "bq40z80_validator.h"
#include "bq40z80_action.h"
#include "bq40z80_data.h"
#include "i2c_helper.h"
#include "i2c.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

#define USE_SCANNER //test if ready

extern uint8_t bq_deviceAddress;

void BQ_Init(I2C_HandleTypeDef *i2c);

void BQ_WriteMABlockCommand(BQ_data* BMS,uint16_t command);
void BQ_ReadMABlockCommand(BQ_data* BMS, uint16_t command, uint8_t *receive, uint8_t size);

uint16_t BQ_ReadCommandAsShort(BQ_data* BMS, uint16_t command);
uint16_t BQ_ReadCommandAsLShort(BQ_data* BMS, uint16_t command);
uint32_t BQ_ReadCommandAsInt(BQ_data* BMS, uint16_t command);
uint8_t BQ_ReadCommandAsChar(BQ_data* BMS, uint16_t command);
uint32_t BQ_ReadCommandAsLInt(BQ_data* BMS, uint16_t command);

void BQ_WriteFlash(BQ_data* BMS, uint16_t addr, uint16_t writeData);
void BQ_WriteFlashByte(BQ_data* BMS, uint16_t addr, uint8_t writeData);

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint16_t Address;
    uint16_t Data;
} FlashData;

FlashData *BQ_GetFlashHex2(void);
FlashData *BQ_GetFlashHex1(void);


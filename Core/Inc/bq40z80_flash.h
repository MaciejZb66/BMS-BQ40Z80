#pragma once
#ifndef __BQ_FLASH__
#include "stdbool.h"

#define __BQ_FLASH__

typedef struct
{
    unsigned short Address;
    unsigned short Data;
} FlashData;

FlashData *BQ_GetFlashHex2(void);
FlashData *BQ_GetFlashHex1(void);
#endif

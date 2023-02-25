#ifndef _SONALKUNJ_WATCHDOG_H_
#define _SONALKUNJ_WATCHDOG_H_

#include "configuration.h"

#define WD0_CLK_EN 0x1
#define WD1_CLK_EN 0x2
#define WD_NON_MASK_INT_EN 0x4
#define WD_RST_INT_EN 0x2
#define WD_EN 0x1

void initWatchDog1(void);

#endif
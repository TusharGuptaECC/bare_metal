#ifndef _ONBOARD_SWITCHES_
#define _ONBOARD_SWITCHES_

#include <stdint.h>
#include "TM4C123.h"

#define switch_one 4	/* used in logic */
#define switch_two 0	/* used in logic */
#define sw1 4 /* bits in gpio port f */
#define sw2 0	/* bits in gpio port f */
#define pullup_mode_switch 0
#define pulldown_mode_switch 1
#define rising_edge_mode_switch 2
#define falling_edge_mode_switch 3

/*function declarations*/
void onBoardSwitchInit(unsigned char switch_name, unsigned char switch_mode);
unsigned char onBoardSwitchRead(unsigned char switch_name);

#endif
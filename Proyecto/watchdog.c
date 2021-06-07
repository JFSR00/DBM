
#include <LPC407x_8x_177x_8x.h>
#include "watchdog.h"

void WD_set(uint32_t sec){
	if(sec < 1){sec = 1;}
	if(sec > 134){sec = 134;}
	LPC_WDT->TC = 125000 * sec;
	LPC_WDT->MOD |= 0x3;
	WD_feed();
}

void WD_feed(void){
	LPC_WDT->FEED = 0xAA;
	LPC_WDT->FEED = 0x55;
}

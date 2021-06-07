
#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <LPC407x_8x_177x_8x.h>

// Esta función configura el watchdog y lo inicia
void WD_set(uint32_t sec);

// Esta función reinicia el watchdog
void WD_feed(void);

#endif /* WATCHDOG_H_ */
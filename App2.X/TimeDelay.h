#ifndef TIMEDELAY_H
#define	TIMEDELAY_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "xc.h"
#include "ChangeClk.h"
// Set up a delay timer
void delay_ms(uint16_t, uint8_t);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

#endif

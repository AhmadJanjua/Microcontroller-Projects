/* 
 * File: TimeDelay.h
 */
#ifndef TIME_DELAY_H
#define	TIME_DELAY_H

#include "xc.h" // include processor files - each processor file is guarded.
#include "TimeDelay.h"

extern unsigned int TMR2flag;
void delay_ms(uint16_t, uint8_t);
void delay_init();
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

#endif	/* TIME_DELAY_H */


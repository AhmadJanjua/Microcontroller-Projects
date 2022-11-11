#ifndef TIMEDELAY_H
#define	TIMEDELAY_H

#include <xc.h> // include processor files - each processor file is guarded.  

extern unsigned int TMR2flag;

void delay_ms(uint16_t, uint8_t);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

#endif

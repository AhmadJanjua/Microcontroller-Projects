#ifndef TIMEDELAY_H
#define TIMEDELAY_H

#include "xc.h"
void delay_ms(int time_ms);
//REQUIRES: argument in ms for the delay requested 
//PROMISES: Starts a timer for the delay, sets the system to idle; then stops the timer when
// the delay has been fulfilled.
void TDinit(void);
//REQUIRES:
//PROMISES: Sets clock speed, enables interrupts,

void switchCLK(char freq);
//PROMISES: Switches clock between 31KHz, 500KHz or 8MHz

#endif
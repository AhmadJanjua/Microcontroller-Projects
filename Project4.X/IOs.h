#ifndef IOS_H
#define IOS_H

#include "xc.h"
void IOinit(void);
//REQUIRES:
//PROMISES: Preprocessor Setup and pin setup to work with the breadboard and LED pin setup.
void IOcheck(void);
//REQUIRES:
//PROMISES: Uses boolean true or false values for pin state to call delay_ms(time) at different values for time
// for different pins/buttons fired.
void swap_state(void);
//REQUIRES:
//PROMISES: Changes state of LED 
#endif


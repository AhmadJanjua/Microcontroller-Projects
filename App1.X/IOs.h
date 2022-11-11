#ifndef IO_H
#define	IO_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "xc.h"
#include "ChangeClk.h"
#include "TimeDelay.h"
#include "UART2.h"

extern uint8_t timerFlag, resume; 
void IOinit(void);
void IOcheck(void);

#endif
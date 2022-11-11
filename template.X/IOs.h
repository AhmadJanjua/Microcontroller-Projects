#ifndef IO_H
#define	IO_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "IOs.h"

extern uint8_t CNflag; 
void IOinit(void);
void IOcheck(void);

#endif
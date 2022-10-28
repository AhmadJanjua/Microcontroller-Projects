/* 
 * File: IOs.h
 */
#ifndef IO_H
#define	IO_H

#include "xc.h"
#include "ChangeClk.h"
#include "TimeDelay.h"
#include "UART2.h"

extern uint8_t CNflag; 
void IOinit(void);
void IOcheck(void);

#endif	/* IO_H */
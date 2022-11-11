/* 
 * File: UART2.h
 */

#ifndef UART2_H
#define	UART2_H

#include "xc.h"
#include "string.h"

void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void);
void InitUART2(void);
void XmitUART2(char, unsigned int);
void Disp2Hex(unsigned int);
void Disp2Hex32(unsigned long int);
void Disp2String(char*);
void Disp2Dec(unsigned int);

#endif	/* UART2_H */


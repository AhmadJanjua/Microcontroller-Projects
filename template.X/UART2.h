#ifndef UART2_H
#define	UART2_H

void InitUART2(void);
void XmitUART2(char, unsigned int);

void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void); 

void Disp2Hex(unsigned int);
void Disp2Hex32(unsigned long int);
void Disp2String(char*);
void Disp2Dec(unsigned int);

#endif
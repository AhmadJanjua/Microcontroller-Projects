#ifndef UART2_H
#define	UART2_H

void InitUART2(void);
void XmitUART2(char, unsigned int);

void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void); 

void Disp2Digit(uint16_t num);
void Disp2String(char*);

#endif
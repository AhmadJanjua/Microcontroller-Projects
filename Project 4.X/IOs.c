/*
 * File:   IOs.c
 * Author: orion
 *
 * Created on October 27, 2022, 10:18 AM
 */


#include "xc.h"

int main(void) {
    return 0;
}


void IOinit(void)
{
    // Set Analog to digital
    AD1PCFGbits.PCFG4 = 1;
    
    // Set input IO; GPIO 7,9,10
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    // Set output IO RB4; GPIO 12
    TRISBbits.TRISB8 = 0;
    
    
    // Set Change notification to be pulled up
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;
    IEC1bits.CNIE = 1; // CN Interrupts enabled
    IPC4bits.CNIP = 6; // Sets CN Interrupt priority
    IFS1bits.CNIF = 0; // clears interrupt flag
    return;
    
    
}

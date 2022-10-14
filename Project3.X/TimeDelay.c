/*
 * File:   TimeDelay.c
 * Author: ahmad
 *
 * Created on October 12, 2022, 6:49 PM
 */


#include "TimeDelay.h"
extern int TMR2flag;
void TDinit() {
    
    INTCON1bits.NSTDIS = 1; // Disable nested interrupts
    
    // Set clock
    SRbits.IPL = 7;  //Disable interrupts
    CLKDIVbits.RCDIV = 0;  // CLK division = 0
    __builtin_write_OSCCONH(0x55);   // (0x00) for 8MHz; (0x66) for 500kHz; (0x55) for 32kHz;
    __builtin_write_OSCCONL(0x01);
    OSCCONbits.OSWEN=1;
    while(OSCCONbits.OSWEN==1) {} 
    SRbits.IPL = 0;  //enable interrupts
    
    // Timer
    T2CONbits.T32 = 0; // Make the timer 16 bits
    T2CONbits.TSIDL = 0; // Continue module operation in idle mode.
    T2CONbits.TCS = 0; // Select internal clock
    
    T2CONbits.TCKPS0 = 0; // Pre-scaler bit 0
    T2CONbits.TCKPS1 = 0; // Pre-scaler bit 1
    
    IEC0bits.T2IE = 1; // Enable interrupt flag
    IFS0bits.T2IF = 0; // Set flag to 0 by default
    
    IPC1bits.T2IP0 = 0; // Set priority bit 0
    IPC1bits.T2IP1 = 0; // Set priority bit 1
    IPC1bits.T2IP2 = 1; // Set priority bit 2
    
    return;
}

// Timer 2 interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF=0; //Clear timer 2 interrupt flag
    T2CONbits.TON=0; //stop timer
    TMR2flag = 1; // global variable created by user
    return;
}


void delay_ms(int delay)
{
    TMR2 = 0;
    PR2 = 16 * delay;
    T2CONbits.TON =1;
    Idle();
    return;
}






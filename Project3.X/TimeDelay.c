/*
 * File:   TimeDelay.c
 * Author: ahmad
 *
 * Created on October 12, 2022, 6:49 PM
 */


#include "TimeDelay.h"

void delay_ms(int delay);

// Timer 2 interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
IFS0bits.T2IF=0; //Clear timer 2 interrupt flag
T2CONbits.TON=0; //stop timer
// TMR2flag = 1; // global variable created by user
}


void delay_ms(int delay){
    T2CONbits.TON=1; // Starting the clock.
    
    IPC1bits.T2IP0=0;
    IPC1bits.T2IP1=1;
    IPC1bits.T2IP2=0; // setting the priority level as 2
    
    IEC0bits.T2IE=1; //enable time interrupt
    IFS0bits.T2IF=0; //flag is disabled.
    
    PR2=16000 * delay;
    
    Idle();
    return;
    
    
    
    
    
}






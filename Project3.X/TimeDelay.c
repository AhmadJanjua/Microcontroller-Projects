/*
 * File:   TimeDelay.c
 * Author: ahmad
 *
 * Created on October 12, 2022, 6:49 PM
 */


#include "TimeDelay.h"

void delay_ms(int time_ms) 
{
    //T2CON Configuration
    T2CON<3> = 0;
    T2CON<15> = 0;
    
    //Timer 2 interrupt config
    // Compute PR2
    Idle(); //Stays here till interrupt
    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF=0; //Clear timer 2 interrupt flag
    T2CONbits.TON=0; //stop timer
    TMR2flag = 1; // global variable created by user
    return;
}
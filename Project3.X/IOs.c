/*
 * File:   IOs.c
 * Author: ahmad
 *
 * Created on October 12, 2022, 6:49 PM
 */

#include "IOs.h"
extern int TMR2flag;
void IOinit(void)
{
    // Switch clock
    SRbits.IPL = 7;  //Disable interrupts
    CLKDIVbits.RCDIV = 0;  // CLK division = 0
    __builtin_write_OSCCONH(0x55);   // (0x00) for 8MHz; (0x66) for 500kHz; (0x55) for 32kHz;
    __builtin_write_OSCCONL(0x01);
    OSCCONbits.OSWEN=1;
    
    while(OSCCONbits.OSWEN==1)
    {} 
    SRbits.IPL = 0;  //enable interrupts   
    
    INTCON1bits.NSTDIS = 1;
    // Timer
    T2CONbits.T32 = 0; // Make the timer 16 bits
    T2CONbits.TSIDL = 0;
    T2CONbits.TCS = 0;
    
    T2CONbits.TCKPS0 = 0;
    T2CONbits.TCKPS1 = 0;
    
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    IPC1bits.T2IP0 = 0;
    IPC1bits.T2IP1 = 0;
    IPC1bits.T2IP2 = 1;
    
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
    
    // Making sure the pull down bits are off
    CNPD1bits.CN0PDE = 0;
    CNPD1bits.CN1PDE = 0;
    CNPD2bits.CN30PDE = 0;
    
    return;
}

void swap_state(void)
{
    LATBbits.LATB8 = !LATBbits.LATB8;
}

void IOcheck(void)
{
    // Always default state is off
    LATBbits.LATB8 = 0;
    // Checks if PB1 and PB2 are clicked
    if (!PORTAbits.RA2 + !PORTAbits.RA4 - !PORTBbits.RB4 == 2 ) { 
        while(!PORTAbits.RA2 + !PORTAbits.RA4 - !PORTBbits.RB4 == 2 ){
            swap_state();
            delay_ms(1);
        }
    }
    // Checks if PB1 is pressed
    else if (!PORTAbits.RA2 & PORTAbits.RA4 & PORTBbits.RB4) {
        // Keep checking if PB1 is pressed
        while(!PORTAbits.RA2 & PORTAbits.RA4 & PORTBbits.RB4) {
            swap_state();
            delay_ms(1000);
        }
    }
    // Checks if PB2 is pressed
    else if (PORTAbits.RA2 & !PORTAbits.RA4 & PORTBbits.RB4) {
        // Keep checking if PB2 is pressed
        while(PORTAbits.RA2 & !PORTAbits.RA4 & PORTBbits.RB4) {
            swap_state();
            delay_ms(2000);    
        }
    }
    // Checks if PB3 is pressed
    else if (PORTAbits.RA2 & PORTAbits.RA4 & !PORTBbits.RB4) {
        // Keep checking if PB3 is pressed
        while(PORTAbits.RA2 & PORTAbits.RA4 & !PORTBbits.RB4) {
           swap_state();
           delay_ms(3000);
        }
    }
    // When no buttons are pressed, led is off
    else {
        LATBbits.LATB8 = 0; // Set led off
    }
    return;
}

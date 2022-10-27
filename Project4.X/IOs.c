/*
 * File:   IOs.c
 * Author: ahmad
 *
 * Created on October 12, 2022, 6:49 PM
 */

#include "IOs.h"
#include "TimeDelay.h"
#include "UART2.h"

// Global flags
int PB1flag = 0, PB2flag = 0, PB3flag = 0;
int twoFlag = 0, threeFlag = 0;

void IOinit(void)
{
    // Switch clock
    SRbits.IPL = 7;  //Disable interrupts
    CLKDIVbits.RCDIV = 0;  // CLK division = 0
    __builtin_write_OSCCONH(0x00);   // (0x00) for 8MHz; (0x66) for 500kHz; (0x55) for 32kHz;
    __builtin_write_OSCCONL(0x01);
    OSCCONbits.OSWEN=1;
    
    while(OSCCONbits.OSWEN==1)
    {} 
    SRbits.IPL = 0;  //enable interrupts   
    
    INTCON1bits.NSTDIS = 0;
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
    
    // CN interrupt init
    // Enable interrupts
    CNEN1bits.CN0IE = 1;
    CNEN1bits.CN1IE = 1;
    CNEN2bits.CN30IE = 1;
    
    // Clear flags
    IPC4bits.CNIP = 6; // set priority
    IFS1bits.CNIF = 0; //clear flag
    IEC1bits.CNIE = 1; //enable interrupt
    
    // Always default state is off
    LATBbits.LATB8 = 0;
    return;
}

void swap_state(void)
{
    LATBbits.LATB8 = !LATBbits.LATB8;
}

void IOcheck(void)
{

    // Checks if PB1 and PB2 are clicked
    if ( twoFlag == 1) { 
        while(twoFlag == 1 ){
            if(PORTAbits.RA2==0 && PORTAbits.RA4==0 ){
               
                Disp2String ("PB1 and PB2 are pressed");
                
            }
            if(PORTAbits.RA4==0 && PORTBbits.RB4==0 ){
                
                Disp2String ("PB2 and PB3 are pressed");
                
            }
            if(PORTAbits.RA2==0 && PORTBbits.RB4==0 ){
                
                Disp2String ("PB1 and PB3 are pressed");
                
            }
        }
    }
    // Checks if PB1 is pressed
    else if (PB1flag == 1) {
        Disp2String(" PB1 is pressed");
        // Keep checking if PB1 is pressed
        while(PB1flag == 1) {
            swap_state();
            delay_ms(500);
        }
    }
    // Checks if PB2 is pressed
    else if (PB2flag == 1) {
        Disp2String(" PB2 is pressed");
        // Keep checking if PB2 is pressed
        while(PB2flag == 1) {
            swap_state();
            delay_ms(2000);    
        }
    }
    // Checks if PB3 is pressed
    else if (PB3flag == 1) {
        Disp2String(" PB3 is pressed");
        // Keep checking if PB3 is pressed
        while(PB3flag == 1) {
           swap_state();
           delay_ms(3000);
        }
    }
    
    
    else if (threeFlag==1){
        Disp2String ("All PB's Pressed");
        LATBbits.LATB8 = 1;
        
        while(threeFlag==1) {
           //swap_state();
            
           
           //delay_ms(3000);
        }
        
    }
    // When no buttons are pressed, led is off
    else {
        LATBbits.LATB8 = 0; // Set led off
    }
    return;
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    Nop();
    // Reset all flags
    PB1flag = PB2flag = PB3flag = twoFlag = threeFlag = 0;
    
    //delay_ms(10);
    
    if(PORTAbits.RA2 == 0 || PORTAbits.RA4 == 0 || PORTBbits.RB4 == 0) {
        
        PORTBbits.RB8 = 0;
        
        if((PORTAbits.RA2 + PORTAbits.RA4 + PORTBbits.RB4)  == 0){
           threeFlag = 1;           
        }
        else if((PORTAbits.RA2 + PORTAbits.RA4 + PORTBbits.RB4)  < 2) {
            twoFlag = 1;
        }
        else if (PORTAbits.RA2 == 0)
        {
            PB1flag = 1;
        }
        else if (PORTBbits.RB4 == 0)
        {
            PB2flag = 1;
        }
        else if (PORTAbits.RA4 == 0)
        {
           PB3flag = 1;
        }
    }
    IFS1bits.CNIF = 0; // clear IF flag
    delay_ms(100);
    //Nop();
}



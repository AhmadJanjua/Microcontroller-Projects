/*
 * File:   IOs.c
 * Author: Rushi V
 *
 * Created on September 30, 2020, 11:33 AM
 */


#include "xc.h"
#include "ChangeClk.h"
#include "TimeDelay.h"
#include "IOs.h"
#include "UART2.h"

// Global flags
int PB1flag = 0, PB2flag = 0, PB3flag = 0;
int twoFlag = 0, threeFlag = 0, nothingFlag = 1;

// IOCheck with Timers
void IOcheck(void)
{
    // Check if all the buttons are pressed
    if ( threeFlag == 1 ) {
        Disp2String ("All PBs pressed\n\r");
        while(threeFlag == 1) {
            PORTBbits.RB8 = 1;
        }
    }
    // Checks if PB1 and PB2 are clicked
    else if ( twoFlag == 1) { 
        NewClk(8);
        if(PORTAbits.RA2==0 && PORTAbits.RA4==0 ){
            Disp2String ("PB1 and PB2 are pressed\n\r");      
        }
        else if(PORTAbits.RA4==0 && PORTBbits.RB4==0 ){
            Disp2String ("PB2 and PB3 are pressed\n\r");
        }
        if(PORTAbits.RA2==0 && PORTBbits.RB4==0 ){
            Disp2String ("PB1 and PB3 are pressed\n\r");
        }
        NewClk(32);
        while(twoFlag == 1 ){
            PORTBbits.RB8 = 1;
        }
    }
    // Checks if PB1 is pressed
    else if (PB1flag == 1) {
        NewClk(8);
        Disp2String("PB1 is pressed\n\r");
        // Keep checking if PB1 is pressed
        NewClk(32);
        while(PB1flag == 1) {
            PORTBbits.RB8 = !PORTBbits.RB8;
            delay_ms(500, 1);
        }
    }
    // Checks if PB2 is pressed
    else if (PB2flag == 1) {
        NewClk(8);
        Disp2String("PB2 is pressed\n\r");
        // Keep checking if PB2 is pressed
        NewClk(32);
        while(PB2flag == 1) {
            PORTBbits.RB8 = !PORTBbits.RB8;
            delay_ms(2000, 1);    
        }
    }
    // Checks if PB3 is pressed
    else if (PB3flag == 1) {
        NewClk(8);
        Disp2String("PB3 is pressed\n\r");
        // Keep checking if PB3 is pressed
        NewClk(32);
        while(PB3flag == 1) {
           PORTBbits.RB8 = !PORTBbits.RB8;
           delay_ms(3000, 1);
        }
    }
    // When no buttons are pressed, led is off
    else if ( nothingFlag == 1) {
        NewClk(8);
        Disp2String( "Nothing pressed\n\r" );
        LATBbits.LATB8 = 0; // Set led off
        while(nothingFlag == 1){;}
    }
    return;
}

//// IOinit() with IO interrupts
void IOinit(void)
{
    TRISBbits.TRISB8 = 0; // Make GPIO RB8 as a digital output
    LATBbits.LATB8 = 0; // Make GPIO RB8 as a digital output
    
    TRISAbits.TRISA4 = 1; // Makes GPIO RA4 as a digital input
    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0
    CNEN1bits.CN0IE = 1;  // enable CN on CN0
    
    TRISBbits.TRISB4 = 1; // Makes GPIO RB4 as a digital input
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RA4/CN0
    CNEN1bits.CN1IE = 1;  // enable CN on CN1
    
    TRISAbits.TRISA2 = 1; // Makes GPIO RA2 as a digital input
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA4/CN0
    CNEN2bits.CN30IE = 1;  // enable CN on CN30
    
    //CN Interrupt settings
    IPC4bits.CNIP = 6; //7 is highest priority, 1 is lowest, 0 is disabled interrupt
    IFS1bits.CNIF = 0; // Clear interrupt flag
    IEC1bits.CNIE = 1; //Enable CN interrupts
    
    return;
}

///// Change of pin Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IEC1bits.CNIE = 0; //disable CN interrupts to avoid debounces 
    PB1flag = PB2flag = PB3flag = twoFlag = threeFlag = nothingFlag = 0;
    NewClk(32);
    delay_ms(200,1);   // 200 msec delay to filter out debounces 
    NewClk(8);
    if(PORTAbits.RA2 == 0 || PORTAbits.RA4 == 0 || PORTBbits.RB4 == 0) {
        PORTBbits.RB8 = 0;
        
        if((PORTAbits.RA2 + PORTAbits.RA4 + PORTBbits.RB4)  == 0){
           threeFlag = 1;           
        }
        else if((PORTAbits.RA2 + PORTAbits.RA4 + PORTBbits.RB4)  < 2) {
            twoFlag = 1;
        }
        else if (PORTAbits.RA2 == 0) {
            PB1flag = 1;
        }
        else if (PORTBbits.RB4 == 0) {
            PB2flag = 1;
        }
        else if (PORTAbits.RA4 == 0) {
           PB3flag = 1;
        }
    }
    else {
        nothingFlag = 1; 
    }
    NewClk(32);
    delay_ms(200,1);   // 200 msec delay to filter out debounces 
    NewClk(8);
    IFS1bits.CNIF = 0;		// clear IF flag
    IEC1bits.CNIE = 1; //Enable CN interrupts to detect pb release    
    return;
}

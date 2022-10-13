 /*
 * File:   main.c
 * Author: Ahmad Janjua
 *
 * Created on September 22, 2022, 6:41 PM
 */


#include "xc.h"

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

int main(void) {
    
    // Set input IO; GPIO 7,9,10
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    // Set output IO RB4; GPIO 12
    TRISBbits.TRISB8 = 0;
    
    // Set Analog to digital
    AD1PCFGbits.PCFG4 = 1;
    
    // Set Change notification to be pulled up
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;
    // Making sure the pull down bits are off
    CNPD1bits.CN0PDE = 0;
    CNPD1bits.CN1PDE = 0;
    CNPD2bits.CN30PDE = 0;
    
    // Counter
    long int i;
    
    while(1)
    {
        // Checks if two or more buttons are clicked
        if( PORTAbits.RA2 + PORTAbits.RA4 + PORTBbits.RB4 < 2 ) {
            LATBbits.LATB8 = 1; // Set led on
        }
        // Checks if PB1 is pressed
        else if (!PORTAbits.RA2) {
            // Resets bit to
            LATBbits.LATB8 = 0;
            // Keep checking if PB1 is pressed
            while(!PORTAbits.RA2) {
                // Swap the button state
                LATBbits.LATB8 = !LATBbits.LATB8; // Set led on
                // Reset counter
                i = 0;
                // Check if buttons are clicked and cycle for 1 second
                while( !PORTAbits.RA2 && PORTAbits.RA4 && PORTBbits.RB4
                        && i != 85225)
                    i++;
            }
        }
        
        // Checks if PB2 is pressed
        else if (!PORTAbits.RA4) {
            // Resets bit to
            LATBbits.LATB8 = 0;
            // Keep checking if PB2 is pressed
            while(!PORTAbits.RA4) {
                // Swap the button state
                LATBbits.LATB8 = !LATBbits.LATB8; // Set led on
                // Reset counter
                i = 0;
                // Check if other buttons are clicked and cycle for 2 seconds
                while( PORTAbits.RA2 && !PORTAbits.RA4 && PORTBbits.RB4
                        && i != 170656)
                    i++;
            }
        }
        // Checks if PB3 is pressed
        else if (!PORTBbits.RB4) {
            // Resets bit to
            LATBbits.LATB8 = 0;
            // Keep checking if PB3 is pressed
            while(!PORTBbits.RB4) {
                // Swap the button state
                LATBbits.LATB8 = !LATBbits.LATB8; // Set led on
                // Reset counter
                i = 0;
                // Check if other buttons are clicked and cycle for 3 seconds
                while( PORTAbits.RA2 && PORTAbits.RA4 && !PORTBbits.RB4
                        && i != 256088)
                    i++;
            }
        }
        // When no buttons are pressed, led is off
        else {
            LATBbits.LATB8 = 0; // Set led off
        }
    }
    return 0;
}
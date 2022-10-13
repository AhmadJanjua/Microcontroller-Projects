/*
 * File:   main.c
 * Author: Ahmad J
 * UCID: 30118441
 * Created on September 10, 2022, 8:38 AM
 */

#include "xc.h"

int main(void) {
    
    // Set RA0-GPIO2, RA1-GPIO3, RA4-GPIO10, RA6-GPIO14 as inputs
    TRISA |= 0x0053;
    
    // Set these registers as outputs
    // RB0-GPIO4,  RB1-GPIO5,   RB2-GPIO6
    // RB4-GPIO9,  RB7-GPIO11,  RB8-GPIO12
    // RB9-GPIO13, RB12-GPIO15, RB13-GPIO16
    TRISB &= 0xcc68;
    
    // Infinite loop
    while(1)
    {
        asm("nop");
        uint16_t input = PORTA & 0x0053;
        // Input is 1
        if( input == 0x0001)
        {
            // Set output to 3
            // Turn bits on
            LATB |= 0x0007;
            // Turn bits off
            LATB &= 0xCC6F;
        }
        // Input is 3, 4 or 8 or 9
        else if( input == 0x0003 || input == 0x0010 || 
                 input == 0x0040 || input == 0x0041)
        {
            // Set output to 1
            // Turn bits on
            LATB |= 0x0001;
            // Turn bits off
            LATB &= 0xCC69;
        }
        // Input is 5
        else if( input == 0x0011)
        {
            // Set output to 8
            // Turn bits on
            LATB |= 0x1397;
            // Turn bits off
            LATB &= 0xDFFF;
        }
        // Input is 6 or 7
        else if( input == 0x0012 || input == 0x0013)
        {
            // Set output to 4
            // Turn bits on
            LATB |= 0x0017;
            // Turn bits off
            LATB &= 0xCC7F;
        }
        // Input is 0, 2 or anything else
        else
        {
            // Set output to 0
            // Turn all bits off
            LATB &= 0xCC68;
        }
    }
    
    return 0;
}

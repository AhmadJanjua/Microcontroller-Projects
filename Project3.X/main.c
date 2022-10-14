 /*
 * File:   main.c
 * Author: Ahmad Janjua
 *
 * Created on September 22, 2022, 6:41 PM
 */


#include "xc.h"
#include "IOs.h"
#include "TimeDelay.h"

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

int TMR2flag = 1;

int  main(void) {
    
    IOinit();
    TDinit();
       
    while(1)
        IOcheck(); 
    return 0;
}
/*
 * File:   main.c
 * Author: Rushi V
 *
 * Created on September 26, 2020, 9:17 PM
 */

// MPLAB header libraries
#include <xc.h>

#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files

#include "ChangeClk.h"
#include "TimeDelay.h"
#include "IOs.h"
#include "UART2.h"

// PRE-PROCESSOR DIRECTIVES - CONFIGURATION BITS

// Code protection 
#pragma config BSS = OFF // Boot segment code protect disabled
#pragma config BWRP = OFF // Boot sengment flash write protection off
#pragma config GCP = OFF // general segment code protecion off
#pragma config GWRP = OFF

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

// WDT
#pragma config FWDTEN = OFF // WDT is off
#pragma config WINDIS = OFF // STANDARD WDT/. Applicable if WDT is on
#pragma config FWPSA = PR32 // WDT is selected uses prescaler of 32
#pragma config WDTPS = PS1 // WDT postscler is 1 if WDT selected

//MCLR/RA5 CONTROL
#pragma config MCLRE = ON // RA5 pin configured as input, MCLR reset on RA5 diabled

//BOR  - FPOR Register
#pragma config BORV = LPBOR // LPBOR value=2V is BOR enabled
#pragma config BOREN = BOR0 // BOR controlled using SBOREN bit
#pragma config PWRTEN = OFF // Powerup timer disabled
#pragma config I2C1SEL = PRI // Default location for SCL1/SDA1 pin

//JTAG FICD Register
#pragma config BKBUG = OFF // Background Debugger functions disabled
#pragma config ICS = PGx2 // PGC2 (pin2) & PGD2 (pin3) are used to connect PICKIT3 debugger

// Deep Sleep RTCC WDT
#pragma config DSWDTEN = OFF // Deep Sleep WDT is disabled
#pragma config DSBOREN = OFF // Deep Sleep BOR is disabled
#pragma config RTCOSC = LPRC// RTCC uses LPRC 32kHz for clock
#pragma config DSWDTOSC = LPRC // DeepSleep WDT uses Lo Power RC clk
#pragma config DSWDTPS = DSWDTPS7 // DSWDT postscaler set to 32768 


// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //

// Global variables
uint8_t CNflag = 0;
uint16_t i = 0;


//MAIN
void main(void) {
    //Clock output on REFO/RB15 - Testing purposes only
     TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
     REFOCONbits.ROEN = 1; // Ref oscillator is enabled
     REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
     REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
     REFOCONbits.RODIV = 0b0000;
     
    // Change Clock of MCU - Adjust UART Baud rate on PC accordingly
     NewClk(32); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
     
   // Initialize IOs for low-power wake-up
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    IOinit();         // enables IO and CN interrupts on Push buttons
    InitUART2();      //Initialize UART settings and enable UART module
    
    while(1)
    {
        
        /*-- Display Commands --*/      
        XmitUART2('G', 5);    // Xmits char 'G' 5 times via UART2 
        XmitUART2('\n',1);    // Xmits New line ASCII command via UART2    
        XmitUART2('\r',1);    // Xmits Carriage Return ASCII command via UART2
        
        Disp2String("\r Hello U of C - Today is day ");
        Disp2Dec(i);
        Disp2Hex(i);
        i=i+1;
        XmitUART2('\n',1);    // Xmits New line ASCII command via UART2    
        XmitUART2('\r',1);    // Xmits Carriage Return ASCII command via UART2
        
        Disp2String("\r PORTA is: ");   
        Disp2Hex(PORTA);        //Xmits PORTA values via UART in 16bit Hex form
        XmitUART2('\n',1);    // Xmits New line ASCII command via UART2    
        XmitUART2('\r',1);    // Xmits Carriage Return ASCII command via UART2
        
        double f;
        char str[10];
        f= -15.5678;
        sprintf(str, "%1.5f", f); // translates -15.5678 into array of char called str[]]
        Disp2String(str);         //Display str[]
        XmitUART2('\n',1);        // Xmits New line ASCII command via UART2
        XmitUART2('\r',1);        // Xmits Carriage Return ASCII command via UART2
        
        
        signed int d;
        //char str[10];
        d =-58;                       
        sprintf(str, "%1.0d", d);     // translates -15.5678 into array of char called str[]    
        Disp2String(str);             //Display str[]
        XmitUART2('\n',1);            // Xmits New line ASCII command via UART2
        XmitUART2('\r',1);            // Xmits Carriage Return ASCII command via UART2
        
        
        LATBbits.LATB8 = 1;             //Turn on LED
        Idle();                       // Put MCU in idle mode - OPTIONAL
        
    }
    
    return;
}
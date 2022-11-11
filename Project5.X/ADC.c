/*
 * File:   ADC.c
 * Author: ahmad
 *
 * Created on November 10, 2022, 9:01 PM
 */
#include "ADC.h"
void ADCinit() {
    // Configure1 bits
    AD1CON1bits.ADON = 0;       // Power the ADC module on
    AD1CON1bits.FORM = 0b00;    // Data output format
    AD1CON1bits.SSRC = 0b111;   // Auto convert Software Controlled
    AD1CON1bits.ASAM = 0b0;     // Sampling begins when SAMP is set
    AD1CON1bits.DONE = 0b1;     // A/D conversion done *MAYBE NEEDED*
    
    // Configure2 bits
    AD1CON2bits.VCFG = 0b000;   // Use Vdd and Vss from computer
    AD1CON2bits.CSCNA = 0;      // Do not scan for inputs
    AD1CON2bits.BUFM = 0;       // Use one 16-word buffer
    AD1CON2bits.ALTS = 0;       // Always use MUX A for multiplexing setting
    // Only if interrupt used
    AD1CON2bits.SMPI = 0b0000;  // Interrupts at the completion of a conversion sequence
    
    // Configure3 bits
    AD1CON3bits.ADRC = 0;       // Use system clk; runs in sleep mode
    AD1CON3bits.SAMC = 0b11111; // Sampling rate
    //AD1CON3bits.ADCS = 0b11111; // CLK prescaler if ADRC = 1;
    
    // Input Selection
    AD1CHSbits.CH0NA = 0;       // Negative input is VR-
    AD1CHSbits.CH0SA = 0b0101;  // Positive input is AN5
    
    AD1PCFGbits.PCFG5 = 0;      // Configure pin AN5 in analog mode
    
    AD1CSSL = 0;
}

uint16_t do_ADC(void) {
    AD1CON1bits.ADON = 1;       // Power the ADC module on
    
    AD1CON1bits.SAMP = 1;           // start sampling...
    NewClk(32);
    delay_ms(400,1);
    NewClk(8);
    AD1CON1bits.SAMP = 0;    
    while (!AD1CON1bits.DONE){};    // conversion done?
    
    AD1CON1bits.ADON = 0;       // Power the ADC module on
    return ADC1BUF0;
}

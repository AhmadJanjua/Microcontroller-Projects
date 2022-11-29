#include "IOs.h"

// Global variables
uint8_t CNflag;

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

// IOCheck with Timers
void IOcheck(void)
{
    IEC1bits.CNIE = 0; //disable CN interrupts to avoid de-bounces
    // Delay to avoid de-bounce
    NewClk(32);
    delay_ms(200,1);
    NewClk(8);
    IEC1bits.CNIE = 1; //disable CN interrupts to avoid de-bounces
    
    if(CNflag == 1){
        Disp2String("b1\r\n");
    }
    else if (CNflag == 2) {
        Disp2String("b2\r\n");
    }
    else if (CNflag == 3) {
        Disp2String("b3\r\n");
    }
    CNflag = 0;
    return;
}

///// Change of pin Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{     
    if(PORTAbits.RA2 == 0){
        CNflag = 1;
    }
    else if (PORTBbits.RB4 == 0) {
        CNflag = 2;
    }
    else if (PORTAbits.RA4 == 0) {
        CNflag = 3;
        resume = !resume;
    }
	IFS1bits.CNIF = 0;		// clear IF flag
    return;
}
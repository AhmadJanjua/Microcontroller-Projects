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
    if(CNflag == 1){
        // Send signal of button press to UART
        Disp2String("aaa\r\n");
    }
    else if (CNflag == 2) {
        // Send signal of button press to UART
        Disp2String("bbb\r\n");
    }
    else if (CNflag == 3) {
        // Send signal of button press to UART
        Disp2String("ccc\r\n");
        WDTexec();
    }
    CNflag = 0;
    return;
}

///// Change of pin Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IEC1bits.CNIE = 0; //disable CN interrupts to avoid de-bounces
    // Delay to avoid de-bounce
    delay_ms(200,1);
    NewClk(8);
    
    if(PORTAbits.RA2 == 0){
        CNflag = 1;
    }
    else if (PORTBbits.RB4 == 0) {
        CNflag = 2;
        // Set to idle or not
        resume = !resume;
    }
    else if (PORTAbits.RA4 == 0) {
        CNflag = 3;
    }
	IFS1bits.CNIF = 0;	// clear IF flag
    IEC1bits.CNIE = 1;  //disable CN interrupts to avoid de-bounces
    
    return;
}
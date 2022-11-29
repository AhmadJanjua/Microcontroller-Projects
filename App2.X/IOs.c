#include "IOs.h"

// Global variables
uint8_t min, sec, CNflag;

void printNum() {
    Disp2Digit(min);
    Disp2String("m : ");
    Disp2Digit(sec);
    Disp2String("s\r\n");
}

void countDown() {
    
    if(!min && !sec) {
        // Nothing
    } else if(!sec) {
        sec = 59;
        min--;
    } else {
        --sec;
    }
    
    if(!min && !sec) {
        resume = 0;
        Disp2String("00m : 00s -- ALARM\r\n");
        LATBbits.LATB8 = 1;           
    } else {
        LATBbits.LATB8 = !LATBbits.LATB8; 
        printNum();       
    }
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

// IOCheck with Timers
void IOcheck(void)
{
    if(CNflag == 1){
        while(CNflag == 1) {
            sec = ++sec%60;
            printNum();
            delay_ms(300,1);
            NewClk(8);
        }
    }
    else if (CNflag == 2) {
        while(CNflag == 2) {
            min = ++min%60;
            printNum();
            delay_ms(300,1);
            NewClk(8);
        }
    }
    else if (CNflag == 3) {
        resume = !resume;
    }
    else if (CNflag == 4) {
        min = 0;
        sec = 0;
        LATBbits.LATB8 = 0;
        Disp2String("00m : 00s\r\n");
    }
    CNflag = 0;
    return;
}

///// Change of pin Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IEC1bits.CNIE = 0; //disable CN interrupts to avoid de-bounces
    
    // Delay to avoid de-bounce
    NewClk(32);
    delay_ms(400,1);
    NewClk(8);
    
    // Reset timer flag
    timerFlag = 0;
    resume = 0;
    
    if(PORTAbits.RA2 == 0){
        CNflag = 1;
    }
    else if (PORTBbits.RB4 == 0) {
        CNflag = 2;
    }
    else if (PORTAbits.RA4 == 0) {
        CNflag = 3;
        
        delay_ms(3000,0);
        while(PORTAbits.RA4 == 0){
            if(timerFlag == 1) {
                CNflag = 4;
                break;
            }   
        }
        NewClk(8);
        T2CONbits.TON=0; // Stop timer
    }
    else if (PORTAbits.RA4 == 1 && (CNflag == 3 || CNflag == 4)){}
    else {
        CNflag = 0;
    }
	IFS1bits.CNIF = 0;		// clear IF flag
    IEC1bits.CNIE = 1; //Enable CN interrupts to detect Pb release
    return;
}
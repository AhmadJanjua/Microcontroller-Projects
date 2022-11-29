#include "main.h"

// Global variables
uint8_t resume = 0;

int main(void) {   
   // Initialize IOs for low-power wake-up
    AD1PCFG = 0xFFFF;   // Turn all analog pins as digital
    timerInit();        // Initialize timer
    IOinit();           // enables IO and CN interrupts on Push buttons
    InitUART2();        //Initialize UART settings and enable UART module
    ADCinit();          // Initialize the ADC
    NewClk(8);
    RCONbits.WDTO = 0; // Resets Watchdog Timer Flag
    while(1)
    {
        if(resume) {
            Disp2Digit(do_ADC());
            Disp2String("\r\n");
            delay_ms(200,1);
            NewClk(8);
        }        
        if(!resume) {
            Idle();
        }
        IOcheck();
    }
    return 0;
}
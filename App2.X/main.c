#include "main.h"

// Global variables
uint8_t resume = 0;

int main(void) {   
   // Initialize IOs for low-power wake-up
    AD1PCFG = 0xFFFF;   // Turn all analog pins as digital
    timerInit();        // Initialize timer
    IOinit();           // enables IO and CN interrupts on Push buttons
    InitUART2();        //Initialize UART settings and enable UART module
    
    while(1)
    {
        if(resume) {
          delay_ms(1000,1);
          NewClk(8);
        }        
        else {
            Idle();
            IOcheck();
        }
    }
    return 0;
}
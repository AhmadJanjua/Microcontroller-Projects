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
    NewClk(8);          // Set clock to 8MHz
    RCONbits.WDTO = 0; // Resets Watchdog Timer Flag
    while(1)
    {
        // Check to see if its resumed
        if(resume) {
            // Check analog input and send to UART
            Disp2Digit(do_ADC());
            Disp2String("\r\n");
            // Delay the signal
            delay_ms(200,1);
            // Change clock back from 32kHz
            NewClk(8);
        }       
        // Check if the machine should idle
        if(!resume) {
            Idle();
        }
        // Check IO
        IOcheck();
    }
    return 0;
}
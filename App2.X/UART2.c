#include "xc.h"
#include "UART2.h"
#include "string.h"

unsigned int clkval;

///// Initialization of UART 2 module.
//// From Section 18 of PIC24F Datasheet
//// configures UART2 module on pins RB0 (Tx) and RB1 (Rx) on PIC24F16KA101 
//// Enables UART2 

void InitUART2(void) 
{

	TRISBbits.TRISB0=0; // Set U2TX/RB0/pin 4 as UART TX
	TRISBbits.TRISB1=1; // Set U2RX/RB1/pin 5 as UART RX
	LATBbits.LATB0=1;

	// configure UART mode i.e Parity, char length etc 
    U2MODE = 0b1000000000001000;
    
    //configure baud rate based on sys clock
	if (OSCCONbits.COSC == 0b110)
	{
		U2BRG = 12;	// gives a baud rate of 4807.7 Baud with 500kHz clock; Set Baud to 4800 on realterm
	}
	else if (OSCCONbits.COSC == 0b101)
	{
		U2BRG = 12;	// gives a baud rate of 300 Baud with 32kHz clock; set Baud to 300 on realterm
	}
	else if (OSCCONbits.COSC == 0b000)
	{
		U2BRG=103;	// gives a baud rate of 9600 with 8MHz clock; set Baud to 9600 on real term
	}
	// Initialize UART Status reg - Tx interrupt control
	U2STA = 0b0010000000000000;
    	
    //Configure Interrupts (for Tx)
    IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
    IPC7bits.U2TXIP = 3;    // UART2 TX interrupt has interrupt priority 3-4th highest priority
    IEC1bits.U2TXIE = 1;	// Disable Transmit Interrupts
	
    //Configure Interrupts (for Rx)
    IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	IPC7bits.U2RXIP = 4;    //UART2 Rx interrupt has 2nd highest priority
    IEC1bits.U2RXIE = 1;	// Enable Recieve Interrupts

	U2MODEbits.UARTEN = 1;	// And turn the peripheral on

	U2STAbits.UTXEN = 1;
	return;
}



///// Xmit UART2: 
///// Displays 'DispData' on PC terminal 'repeatNo' of times using UART to PC. 
///// Adjust Baud on real term as per clock: 
////  32kHz clock - Baud=300 ; 500kHz clock - Baud=4800; 8MHz clock - Baud=9600 

void XmitUART2(char CharNum, unsigned int repeatNo)
{	
   // InitUART2();	//Initialize UART2 module at start of main()
   
	while(repeatNo!=0) 
	{
		while(U2STAbits.UTXBF==1)	//Just loop here till the FIFO buffers have room for one more entry
		{
			Idle();
		}	
		U2TXREG=CharNum;	//Move Data to be displayed in UART FIFO buffer
		repeatNo--;
	}
	while(U2STAbits.TRMT==0)	//Turn off UART2 upon transmission of last character; also can be Verified in interrupt subroutine U2TXInterrupt()
	{
		
	}
	// U2MODEbits.UARTEN = 0;	// turn off UART module to save power - OPTIONAL

	return;
}

// Displays 16 bit number DispNum in Decimal form using UART2
void Disp2Digit(uint16_t DispNum)
{
    char rem[5] = {0,0,0,0,0}; // array to store remainders
    char rem1;
    uint8_t i=0; 
    for(i = 0; i<5; i++) {
        rem[i] = DispNum%10;
        DispNum = DispNum/10;
    }
    for(i = 5; i>0; i--)
    {
        rem1 = rem[i-1];
        XmitUART2((rem1+48),1);
    }    
    return;
}

//Displays String of characters in str using UART
void Disp2String(char *str) 
{
    unsigned int i;
   // XmitUART2(0x0A,2);  //LF
   // XmitUART2(0x0D,1);  //CR 
    for (i=0; i<= strlen(str); i++)
    {
          
        XmitUART2(str[i],1);
    }
    // XmitUART2(0x0A,2);  //LF
    // XmitUART2(0x0D,1);  //CR 
    
    return;
}

// Interrupt service routine for UART TX
void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
	IFS1bits.U2TXIF = 0;
}
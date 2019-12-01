#include <msp430g2553.h> 
void main(void) { 
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer 
	P1DIR |= 0x01; // Set P1.0 to output direction 
  P1REN |= 0x08;
  P1OUT |= 0x08;
	while (1) {// Infinite Loop  
		if ((BIT3 & P1IN)) { 
			P1OUT &= ~0x01; 
			// if P1.3 is 1(not pressed),reset P1.0 
		}else{ 
			P1OUT |= 0x01; // else set P1.0 
		} 
	} 
}

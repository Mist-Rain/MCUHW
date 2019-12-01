#include <msp430g2553.h> 
void main(void) { 
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer 
	P1DIR |= 0x01; // Set P1.0 to output direction 
	P1IE |= BIT3; // P1.3 interrupt enabled 
	P1IES |= BIT3; // P1.3 Hi/lo edge 
	P1IFG &= ~BIT3; // P1.3 IFG cleared 
	
	_BIS_SR(LPM4_bits + GIE); // Enter LPM4 w/interrupt 
} 
// Port 1 interrupt service routine 
#pragma vector=PORT1_VECTOR 
__interrupt void Port_1(void) { 
	P1OUT ^= 0x01; // P1.0 = toggle 
	P1IES ^= BIT3; 
	P1IFG &= ~BIT3; // P1.3 IFG cleared 
} 

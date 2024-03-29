// Example for switch button 

#include <msp430.h>

#define LED BIT0
#define BUTTON BIT3

void main(void)
{
 WDTCTL = WDTPW|WDTHOLD;
 
 P1DIR = LED;
 P1OUT = LED;

 P1IE = BUTTON;//enable interrupt from port P1
 P1IES = BUTTON;//interrupt edge select from high to low
 P1IFG = 0x00;//clear the interrupt flag

 _enable_interrupts();//enable all interrupts

 while(1); //wait for an interrupt
}

#pragma vector=PORT1_VECTOR
//define the interrupt vector
__interrupt void PORT1_ISR(void){		
// Interrupt Service Routine
 P1OUT ^= 0x01; //toggle LED
 P1IFG = 0x00; //clear the interrupt flag
}

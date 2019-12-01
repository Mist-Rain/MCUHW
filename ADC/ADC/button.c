#include <msp430.h>
#define BUTTON BIT3
int count = 0;
void main(void) {
  WDTCTL = WDTPW|WDTHOLD;
  P1IE = BUTTON;//Enable interrupt from port1
  P1IES = BUTTON;//Interrupt edge select from high to low
  P1REN = BUTTON;
  P1OUT = BUTTON;
  P1IFG = 0x00;//Clear the interrupt flag
  _enable_interrupts();//Enable all interrupts
  while(1);
}
#pragma vector=PORT1_VECTOR
//define the interrupt vector	
__interrupt void PORT1_ISR(void){		
  // Interrupt Service Routine for Port 1
  count += 1;
  P1IFG = 0x00;//Clear the interrupt flag
}

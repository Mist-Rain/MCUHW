#include <msp430g2553.h>
#define BUTTON BIT3
int pwmDirection = 1;

void main(void){
    
    P1IE = BUTTON;//Enable interrupt from port1
    P1IES = BUTTON;//Interrupt edge select from high to low
    P1REN = BUTTON;
    P1OUT = BUTTON;
    P1IFG = 0x00;//Clear the interrupt flag
    _enable_interrupts();//Enable all interrupts

    WDTCTL = WDT_MDLY_32;                 // Watchdog timer ?32ms
    
    IE1 |= WDTIE;                         // enable Watchdog timer interrupts
    
    P1DIR |= BIT6;                        // Green LED for output
    
    P1SEL |= BIT6;                        // Green LED Pulse width modulation
    
    TA0CCR0 = 1000;                       // PWM period
    
    TA0CCR1 = 1;                          // PWM duty cycle, time cycle on vs. off, on 1/1000 initially
    
    TA0CCTL1 = OUTMOD_7;                  // TA0CCR1 reset/set -- high voltage below count and
                                          // low voltage when past
    
    TA0CTL = TASSEL_2 + MC_1;             // Timer A control set to SMCLK clock TASSEL_2, 1MHz
                                          // and count up mode MC_1
    _BIS_SR(LPM0_bits + GIE);             // Enter Low power mode 0
}

#pragma vector=WDT_VECTOR                 // Watchdog Timer interrupt service routine

  __interrupt void watchdog_timer(void) {

    TA0CCR1 += pwmDirection*20;           // Increase/decrease duty cycle, on vs. off time

    if( TA0CCR1 > 980 || TA0CCR1 < 20 )   // Pulse brighter (increasing TA0CCR1) or dimmer
       pwmDirection = -pwmDirection;
}

#pragma vector=PORT1_VECTOR
//define the interrupt vector	
__interrupt void PORT1_ISR(void){		
  // Interrupt Service Routine for Port 1
  if(pwmDirection == 1){
      P1OUT ^= BIT6;   
      P1IFG = ~BIT3;
      TA0CCR1 = 980;
      pwmDirection = -pwmDirection;
  } else if(pwmDirection == -1){
      P1OUT ^= BIT6;   
      P1IFG = ~BIT3;
      TA0CCR1 = 20;
      pwmDirection = -pwmDirection;
  }
}

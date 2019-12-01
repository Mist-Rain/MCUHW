#include <msp430.h>
#define BUTTON BIT3
// Global variables
int adc[10] = {0}; //Sets up an array of 10 integers and zero's the values
int avg_adc = 0;
 
// Function prototypes
void adc_Setup();
void adc_Sam10();
 
void main()
{
	  WDTCTL = WDTPW + WDTHOLD;			// Stop WDT
	  adc_Setup();						// Fucntion call for adc_setup  P1IE = BUTTON;//Enable interrupt from port1
	  P1IES = BUTTON;//Interrupt edge select from high to low
	  P1REN = BUTTON;
	  P1OUT = BUTTON;
	  P1IFG = 0x00;//Clear the interrupt flag
	  _enable_interrupts();//Enable all interrupts
 
	  while(1)                                                                   8
	  {
		  adc_Sam10();		// Function call for adc_samp
		  // Add all the sampled data and divide by 10 to find average
		  avg_adc = ((adc[0]+adc[1]+adc[2]+adc[3]+adc[4]+adc[5]+adc[6]+adc[7]+adc[8]+adc[9]) / 10);
	  }
}
 
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
 
// ADC set-up function
void adc_Setup()
{
	ADC10CTL1 = CONSEQ_2 + INCH_3;						// Repeat single channel, A0
	ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;	// Sample & Hold Time + ADC10 ON + Interrupt Enable
	ADC10DTC1 = 0x0A;									// 10 conversions
	ADC10AE0 |= 0x01;									// P1.0 ADC option select
}
 
// ADC sample conversion function
void adc_Sam10()
{
    ADC10CTL0 &= ~ENC;				// Disable Conversion
    while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
    ADC10SA = (int)adc;				// Transfers data to next array (DTC auto increments address)
    ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
    __bis_SR_register(CPUOFF + GIE);// Low Power Mode 0, ADC10_ISR
}
#pragma vector=PORT1_VECTOR
//define the interrupt vector	
__interrupt void PORT1_ISR(void){		
  // Interrupt Service Routine for Port 1
  if(avg_adc/1000>0.25){
	  P1DIR |= BIT6;
  } else {
	  P1DIR |= BIT0;
  }
}
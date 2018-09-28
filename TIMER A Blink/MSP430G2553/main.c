/*  MSP430G2
    Author: Jacob Okun
    Created: September 26, 2018
    Last Updated: September 28, 2018*/

#include <msp430.h>

void main(void) {
  WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer
  P1DIR |= BIT0;    //sets P1.0 to output
  P1OUT &= ~BIT0;   //turns LED on P1.0 off
  P1DIR |= BIT6;    //sets P1.6 to output
  P1OUT &= ~BIT6;   //turns LED on P1.6 off
  TA0CCR0 = 1000;   //sets TimerA0 period
  TA0CCTL0 = 0x10;  //enable Timer A0 interrupts
  TA0CTL = TASSEL_1 + MC_1; //sets counting mode to UP, chooses ACLK
  TA1CCR0 = 20000;  //sets TimerA1 period
  TA1CCTL0 = 0x10;  //enable Timer A1 interrupts
  TA1CTL = TASSEL_1 + MC_1; //Sets counting mode to UP, chooses ACLK
  _BIS_SR(LPM0_bits + GIE); //low power mode interrupts enabled
}

#pragma vector=TIMER1_A0_VECTOR    

//interrupt service route
__interrupt void Timer1_A0 (void) 
{
   P1OUT ^= BIT0;   //flashes LED on P1.0
}

#pragma vector=TIMER0_A0_VECTOR    

//interrupt service routine
  __interrupt void Timer0_A0 (void) 
  {
   P1OUT ^= BIT6;   //flashes LED on P1.6
}

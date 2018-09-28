/*  MSP430F5529
    Author: Jacob Okun
    Created: September 26, 2018
    Last Updated: September 28, 2018*/

#include <msp430.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer

  P1DIR |= BIT0;    // sets P1.0 to output
  P1OUT &= ~BIT0;   //turns LED on P1.0 off
  P4DIR |= BIT7;    //sets P4.7 to output
  P4OUT &= ~BIT7;   //turns LED on P4.7 off
  TA0CCR0 = 1000;    //TimerA0 period
  TA0CCTL0 = 0x10;  //enables TimerA0 interrupts
  TA0CTL = TASSEL_1 + MC_1; //set count mode to up, choose ACLK
  TA1CCR0 = 20000;  //TimerA1 period
  TA1CCTL0 = 0x10;  //enables TimerA1 interrupts
  TA1CTL = TASSEL_1 + MC_1; //set count mode to up, choose ACLK
  _BIS_SR(LPM0_bits + GIE); //Low power mode interrupts enabled
}

#pragma vector=TIMER1_A0_VECTOR //interrupt service routine

__interrupt void Timer1_A0 (void)
{
      P1OUT ^= BIT0;               //flashes LED on P1.0
}

#pragma vector=TIMER0_A0_VECTOR //interrupt service routine

__interrupt void Timer0_A0 (void)
{
   P4OUT ^= BIT7;                  //flashes LED on P4.7
}

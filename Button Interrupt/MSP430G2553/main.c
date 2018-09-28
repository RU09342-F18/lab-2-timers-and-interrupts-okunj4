/*  MSP430G2
    Author: Jacob Okun
    Created: September 19, 2018
    Last Updated: September 26, 2018*/

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //disable watchdog timers
    P1DIR = BIT0;   //sets P1.0 as an output
    P1REN = BIT3;   //enables pull-up resistor at P1.3
    P1OUT = BIT3;   //initializes the value of P1.3
    P1IE |= BIT3;   //enables interrupt for P1.3
    P1IFG &= ~BIT3; //P1.3 interrupt flags cleared
    __enable_interrupt();   //enables interrupt
}


//interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;  //flashes LED at P1.0
    P1IFG &= ~BIT3; //interrupt flags for button on P1.3 cleared
}

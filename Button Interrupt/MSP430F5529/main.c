/*  MSP430F5529
    Author: Jacob Okun
    Created: September 19, 2018
    Last Updated: September 26, 2018*/
    
#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   //stop watchdog timer
    P1DIR = BIT0;   //sets P1.0 as output
    P1REN = BIT1;   //enables pull on resistor on P1.1
    P1OUT = BIT1;   //initializes the value of P1.1
    P1IE |= BIT1;   //enables interrupt for the button at P1.1
    P1IFG &= ~BIT1; //clears P1.1 interrupt flags
    __enable_interrupt();   //enables interrupt
}

//interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;  //flashes LED at P1.0
    P1IFG &= ~BIT1; //clears P1.1 button interrupt flags.
}

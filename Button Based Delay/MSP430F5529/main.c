/*  MSP430F5529
    Author: Jacob Okun
    Created: September 26, 2018
    Last Updated: September 27, 2018*/

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //stop watchdog timer


    P1OUT &= ~BIT0;  //sets P1.0 LED
    P1DIR |= BIT0;  //sets P1.0 to output
    P1REN |= BIT1; //sets P1.3 pull-up/down resistor to be enabled
    P1OUT |= BIT1; //sets P1.3 to pull-up resister
    P1IE |= BIT1; //enables interrupt on P1.1 button
    P1IES |= BIT1; //enables high to low interrupt on P1.1 button



    TA0CCR0 = 100; //sets initial speed of LEDs
    TA0CCTL0 = CCIE;   //enable TimerA0 interrupt
    TTA0CTL = TASSEL_1 +MC_1 + ID_3;    //set count mode to up, select ACLK, divide by 8

//enables interrupt
__enable_interrupt();
    while (1)
    {
    }
}

//interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer0_A0 ()
    {
        P1OUT ^= BIT0;  //flashes P1.0 LED

    }

//interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IES & BIT1)
    {
        TA0CTL = TACLR; //clear timer
        TA0CTL = TASSEL_1 + MC_2 + ID_3;    //change to continuous mode

        P1IES &= ~BIT1; //low to high edge trigger
    }
    else
    {
        TA0CCR0 = TA0R; //sets timer period to value stored in TA0R
        TA0CTL = TASSEL_1 + MC_1 + ID_3;    //change to continuous mode
        P1IES |= BIT1;  //high to low edge trigger
    }
    P1IFG &= ~BIT1; //clear P1.1 interrupt flags
}

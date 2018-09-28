/*  MSP430G2
    Author: Jacob Okun
    Created: September 26, 2018
    Last Updated: September 28, 2018*/

#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //stop watchdog timer
    BCSCTL3 = LFXT1S_2;
    
    P1DIR |= BIT0;  //sets P1.0 to output
    P1REN |= BIT3;  //enables pull up resistor on P1.3
    P1OUT |= BIT3;  //sets P1.3 to pull up resistor
    P1OUT |= 0X01;  //sets P1.6 to on
    P1OUT &= ~BIT0; //turns P1.0 LED off
    P1IE |= BIT3;   //enables interrupt on P1.3
    P1IES |= BIT3;  //enables hi/lo behavior on interrupt


     CCTL0 = CCIE;  //CCR0 interrupt enabled
     CCR0 =  100;   //sets starting frequency

                            
     TACTL = TASSEL_1 + MC_1 + ID_3;    //SMCLK selected, Continuous mode, enabled Divider = 8

__enable_interrupt(); //enables interrupts
    while (1)
    {
    }
}

//interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer_A ()
    {
        P1OUT ^= BIT0;  //flashes P1.0 LED

    }

///interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IES & BIT3)
    {
        TACTL = TACLR;  //clears timer
        TACTL = TASSEL_1 + MC_2 + ID_3; //change timer to continuous mode


        P1IES &= ~BIT3; //low to high edge trigger
    }
    else
    {

        CCR0 = TA0R; //sets clock frequency to value stored in TA0R
        TACTL = TASSEL_1 + MC_1 + ID_3; //change timer to continuous mode
        P1IES |= BIT3; //high to low edge trigger
    }
    P1IFG &= ~BIT3; //clears interrupt flags on P1.3
}

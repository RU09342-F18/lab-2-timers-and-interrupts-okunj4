### Author: Jacob Okun
### Created: September 28, 2018
### Last Updated: September 28, 2018

# Button Based Delay
The codes in each folder are for their respective boards, the MSP430G2553 and MSP430F5529.  The codes are very similar but are different because of the timer and register.  The MSP430G2553 uses CCR0, and TCTL, and the MSP430F5529 has to have the specific timer to be declared such as TA0CCR0, TA0CCTL0, and TA0CTL.  Both of these codes will initilly blink and LED until the button is pressed.  When the button is pressed the timer will start and and will stop when released.  When relased the LED will blink at the rate of how long the button was held.

## MSP430G2553
The code for the MSP430G2553 will blink the LED at P1.0 until the button is pressed at P1.3.  The clock utilized is the SMCLK.

## MSP430F5529
The code for the MSP430F5529 will blink the LED at P1.0 until the button is pressed at P1.1.  The clock utilized is the ACLK.



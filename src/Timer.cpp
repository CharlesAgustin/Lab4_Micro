// Author:
// Net ID:
// Date:
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1()
{
    // intialize  CTC mode = 0100
    TCCR1B &= (1 << WGM13);  // set WGM3 to 0
    TCCR1B |= (1 << WGM12);  // set WGM2 to 1
    TCCR1A &= ~(1 << WGM11); // set WGM1 to 0
    TCCR1A &= ~(1 << WGM10); // set WGM0 to 0

    // initialze prescalar of 1024 (CS = 101  )
    TCCR1B |= (1 << CS12) | (1 << CS10); // set CS12 and CS10 to be 1
    TCCR1B &= ~(1 << CS11);              // set CS11 to be 0
}

/* This delays the program an amount of seconds specified by unsigned int delay.
 */
void delaySecond(unsigned int delay)
{
    int prescalar = 1024;                     // set the value of prescalar 1024 to calculate
    OCR1A = ((1 * 16000000) / prescalar) - 1; // 15624 tick for 1 second
    for (unsigned int i = 0; i < delay; i++)  // keep on counting until reach the disered value of delay
    {
        TCNT1 = 0; // reset timer counter
        while (!(TIFR1 & (1 << OCF1A)))
            ;                  // do nothing when flag is down
        TIFR1 |= (1 << OCF1A); // set the flag down
    }
}

/* Initialize timer 0, you should not turn the timer on here.
 * You will need to use CTC mode */
void initTimer0()
{
    // intialize  CTC mode = 010
    TCCR0A &= ~(1 << WGM00); // set WGM0 to 0
    TCCR0A |= (1 << WGM01);  // set WGM1 to 1
    TCCR0B &= ~(1 << WGM02); // set WGM2 to 0

    // initialze prescalar of 64 (CS = 011)
    TCCR0B |= (1 << CS01) | (1 << CS00); // set CS01 and CS00 to be 1
    TCCR0B &= ~(1 << CS02);              // set CS02 to be 0
}

/* This delays the program an amount specified by unsigned int delay.
 * Use timer 0. Keep in mind that you need to choose your prescalar wisely
 * such that your timer is precise to 1 millisecond and can be used for
 * 100-2000 milliseconds
 */
void delayMs(unsigned int delay)
{
    int prescalar = 64;                           // set the value of the presacalar for calculation to be 64
    OCR0A = ((0.001 * 16000000) / prescalar) - 1; // 249 tick for 1 milisecond
    for (unsigned int i = 0; i < delay; i++)      // keep on counting until reach the disered value of delay
    {
        TCNT0 = 0; // reset timer counter
        while (!(TIFR0 & (1 << OCF0A)))
            ;                  // do nothing when flag is down
        TIFR0 |= (1 << OCF0A); // set the flag down
    }
}
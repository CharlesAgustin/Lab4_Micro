#include "Switch.h"

void initSwitch()
{
    DDRD &= ~(1 << DDD0);   // initialize D0 (pin 21) to be input
    PORTD |= (1 << PORTD0); // pull up resistor
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt

    // low level of INT interrupt  ISC01=0 ISC00=0
    EICRA &= ~(1 << ISC01);
    EICRA &= ~(1 << ISC00);
}
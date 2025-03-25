#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delaySecond(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay);

#endif

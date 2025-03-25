#ifndef PWM_H
#define PWM_H
#include <avr/io.h>

void initPWMTimer3();
void initPWMPin();
void changeDutyCycle(unsigned int adc);
#endif

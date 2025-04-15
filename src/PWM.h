#ifndef PWM_H
#define PWM_H
#include <avr/io.h>
#include"ADC.h"

void initPWMTimer3();
void initPWMPin();
void changeDutyCycle(MotorState currentState, uint16_t adc);
#endif

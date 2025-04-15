#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

typedef enum
{
    CLOCKWISE,
    COUNTERCLOCKWISE,
    STOP
} MotorState;

void initADC();
unsigned int readADC();
MotorState GetMotorDirection(uint16_t adc_value);

#endif

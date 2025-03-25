#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void initADC();
unsigned int readADC();
unsigned int getMotorState(unsigned int adc_value);

#endif

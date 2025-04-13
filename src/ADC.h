#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void initADC();
unsigned int readADC();
unsigned int DigitalSignal(int16_t adc_value);

#endif

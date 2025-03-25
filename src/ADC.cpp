#include "ADC.h"

// Initialize ADC with AVCC as reference, A0 as input
void initADC()
{
    ADMUX |= (1 << REFS0);  // Set AVCC as reference voltage
    ADMUX &= ~(1 << REFS1); // Clear REFS1 (AVCC reference)
    ADMUX &= 0xF0;          // Select ADC0 (A0) as input

    ADCSRA |= (1 << ADEN);                                // Enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128 (16MHz / 128 = 125kHz)
}

// Read ADC value from A0
unsigned int readADC()
{
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait until conversion completes

    return ADC; // Return 10-bit ADC value (0-1023)
}

// Determine motor state based on potentiometer voltage
unsigned int getMotorState(unsigned int adc_value)
{
    if (adc_value <= 409)      // 0V - 2V  (0-409)
        return 1;              // Clockwise
    else if (adc_value >= 614) // 3V - 5V  (614-1023)
        return 2;              // Counterclockwise
    else                       // 2V - 3V  (409-613)
        return 0;              // Stop
}

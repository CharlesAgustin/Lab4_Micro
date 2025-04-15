#include "ADC.h"

// Initialize ADC with AVCC as reference, A0 as input

#define MAX 0x3FF        // Maximum value of 10 bit ADC
#define MIDDLE (MAX / 2) // Middle point of ADC (to stop)
#define SENSE 20         // to give some tolerance

void initADC()
{
    ADMUX |= (1 << REFS0);                                                                         // Set AVCC as reference voltage (5V)
    ADMUX &= ~(1 << REFS1);                                                                        // Set REFS1 to 0 touse AVCC
    ADMUX &= ~(1 << ADLAR);                                                                        // Right justified
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4) | (1 << MUX5)); // Select ADC0 (A0) as input (single ended)

    ADCSRA &= ~(1 << ADATE);                              // disable ADATE
    ADCSRA &= ~(1 << ADIE);                               // disable the interrupt flag
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128 (16MHz / 128 = 125kHz)

    ADCSRA |= (1 << ADEN); // Enable ADC
}

// Read ADC value from A0
unsigned int readADC() // probably call in main function to be stored in a varibale then used on get motor state
{
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait until conversion completes

    return ADC; // Return 10-bit ADC value (0-1023)
}

// Generate digital signal based on voltage input
MotorState GetMotorDirection(uint16_t adc_value) // int16 is used to ensure that it can hold 16 byte in unsigned
{
    if (adc_value < (MIDDLE - SENSE)) // checking the voltage of input, if it is lower than the middle point - sensitivity, then motor goes clockwise
    {
        return CLOCKWISE;
    }
    else if (adc_value > (MIDDLE + SENSE)) // checking the voltage of input, if it is higher than the middle point + sensitivity, then motor goes counter clockwise
    {
        return COUNTERCLOCKWISE;
    }
    else // if none of those two (meaning input is in middle), then motor stop
    {
        return STOP;
    }
}

#include "ADC.h"

// Initialize ADC with AVCC as reference, A0 as input

void initADC()
{
    ADMUX |= (1 << REFS0);                                                                         // Set AVCC as reference voltage (5V)
    ADMUX &= ~(1 << REFS1);                                                                        // Set REFS1 to 0 to use AVCC
    ADMUX &= ~(1 << ADLAR);                                                                        // Right justified (MSB is the second bit of ADCH)
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4) | (1 << MUX5)); // Select ADC0 (A0) as input (single ended)

    ADCSRA &= ~(1 << ADATE);                              // disable ADATE (disable "auto triggering")
    ADCSRA &= ~(1 << ADIE);                               // disable the interrupt flag
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128 (16MHz / 128 = 125kHz) (ADPS0:2 = 1)

    ADCSRA |= (1 << ADEN); // Enable ADC
}

// Read ADC value from A0
unsigned int readADC() // call in main function to be stored in a varibale then used on Duty Cycle
{
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait until conversion completes

    return ADC; // Return 10-bit ADC value (0-1023)
}

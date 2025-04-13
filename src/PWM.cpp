#include "timer.h"
#include "PWM.h"
#include "ADC.h"

void initPWMTimer3()
{
    // intialize Fast PWM mode 10-bit (TOP = 0x3FF)
    TCCR3B &= ~(1 << WGM33);               // set WGM3 to 0
    TCCR3A |= (1 << WGM31) | (1 << WGM30); // set WGM1 and WGM0 to 1
    TCCR3B |= (1 << WGM32);                // set WGM2 to 1

    // Set non-inverting mode for OCR3A (clear on compare match, set on bottom)
    TCCR3A |= (1 << COM3A1);

    // Set initial duty cycle to 0 (motor off initially)
    OCR3A = 0;
    // Set presclar to 1 because we want the PWM to be fast, creating constant signal
    TCCR3B |= (1 << CS30);
    TCCR3B &= ~((1 << CS31) | (1 << CS32));
}

void initPWMPin()
{
    DDRH |= (1 << DDH5) | (1 << DDH6); // Output to In1 and In2
    DDRB |= (1 << DDB4);               // Output to Enable 1
}
void changeDutyCycle(unsigned int adc)
{
    if (adc > 1023)
        adc = 1023; // Clamp to 10-bit max

    OCR3A = adc; // Set duty cycle for Timer 3, Channel A (Pin PH5)

    // Optional: For dual direction motor control using L293D
    // Based on voltage ranges:
    // 0–2V (adc 0–410): clockwise
    // 2–3V (adc 410–614): stop
    // 3–5V (adc 615–1023): counter-clockwise

    if (adc < 410)
    {
        // Clockwise rotation
        PORTB |= (1 << PB4);  // Enable motor driver channel 1
        PORTH &= ~(1 << PH4); // Disable channel 2
    }
    else if (adc > 614)
    {
        // Counter-clockwise rotation
        PORTB &= ~(1 << PB4); // Disable channel 1
        PORTH |= (1 << PH4);  // Enable channel 2
    }
    else
    {
        // Stop
        PORTB &= ~(1 << PB4);
        PORTH &= ~(1 << PH4);
    }
}
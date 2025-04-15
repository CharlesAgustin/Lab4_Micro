#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#define TOP 0x3FF        // TOP flag of 10 bit PWM
#define MIDDLE (TOP / 2) // Middle point of ADC (to stop)
#define SENSE 20         // to give some tolerance

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
void changeDutyCycle(MotorState currentState, uint16_t adc)
{
    uint16_t duty = 0;    // set Duty Cycle to be initally 0
    switch (currentState) // checking the current state of the motor from ADC
    {
    case CLOCKWISE:
        PORTH |= (1 << PH5);  // turn on direction 1
        PORTH &= ~(1 << PH6); // turn off direction 2
        PORTB |= (1 << PB4);  // turn on enable
        duty = TOP - adc;
        break;
    case COUNTERCLOCKWISE:
        PORTH &= ~(1 << PH5); // turn off direction 1
        PORTH |= (1 << PH6);  // turn on direction 2
        PORTB |= (1 << PB4);  // turn on enable
        duty = adc;
        break;
    case STOP:
        PORTB &= ~(1 << PB4); // turn off enable
        PORTH &= ~(1 << PH5); // turn off direction 1
        PORTH &= ~(1 << PH6); // turn off direction 2
        duty = 0;
        break;
    }
    OCR3A = duty; // Set duty cycle for Timer 3, OCR3A (PH5)
}
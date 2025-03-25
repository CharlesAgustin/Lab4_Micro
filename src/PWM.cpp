#include "timer.h"
#include "PWM.h"

void initPWMTimer3()
{
    // intialize Fast PWM mode = 0111
    TCCR3B &= ~(1 << WGM33);               // set WGM3 to 0
    TCCR3A |= (1 << WGM31) | (1 << WGM30); // set WGM1 and WGM0 to 1
    TCCR3B |= (1 << WGM32);                // set WGM2 to 1

    // Set non-inverting mode for OCR3A and OCR3B (clear on compare match, set on bottom)
    TCCR3A |= (1 << COM3A1) | (1 << COM3B1);

    // Set initial duty cycle to 0 (motor off initially)
    OCR3A = 0;
    OCR3B = 0;
}
void initPWMPin()
{
    DDRH |= (1 << DDH5) | (1 << DDH6);
    DDRB |= (1 << DDB4);
}
void changeDutyCycle(unsigned int adc)
{
    OCR3A = adc;
    OCR3B = adc;
}
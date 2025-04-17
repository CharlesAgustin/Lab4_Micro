#include "Arduino.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#define sense 20 // add some tolerance to the value

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
    DDRE |= (1 << DDE3);               // Output to Enable 1
}
void setMotorDirection(unsigned int direction)
{
    if (direction == 1)
    {                         // CLockwise
        PORTH |= (1 << PH5);  // Set PH3 high
        PORTH &= ~(1 << PH6); // Set PH4 low
    }
    else
    {                         // Counter Clockwise
        PORTH |= (1 << PH6);  // Set PH4 high
        PORTH &= ~(1 << PH5); // Set PH3 low
    }
}
// Adjusts the PWM duty cycle based on ADC result
void changeDutyCycle(unsigned int result)
{

    // Stopping the motor
    if ((unsigned int)(1023 * 0.5) - sense <= result && result <= (unsigned int)(1023 * 0.5) + sense) // if the ADC value is between the middle +- tolerance, then it stops
    {
        OCR3A = 0; // Set OCR3A to 0 to stop motor
    }
    // Full Clockwise
    else if (result == 1023) // if ADC value if 1023, then it goes clockwise at full speed
    {
        setMotorDirection(1); // set the direction to clockwise
        OCR3A = 1023;         // Set OCR3A  to 1023 for full speed
    }

    // Full Counter Clockwise
    else if (result == 0) // if ADC value is 0, then it goes counter clockwise at full speed
    {
        setMotorDirection(0); // set direction to counter clockwise
        OCR3A = 1023;         // Set OCR3A to 1023 for full speed
    }
    // Counter Clockwise — decrease result from 511 to 0
    else if (result < (unsigned int)(1023 * 0.5) - sense) // if ADC value is less than middle-tolerance, but not 0, then it moves counter clockwise at a changing speed (increase or decrease)
    {
        setMotorDirection(0);                                        // set direction to counter clockwise
        OCR3A = (((unsigned int)(1023 * 0.5) - sense) - result) * 2; // increase speed as input moves further from midpoint
    }

    // Clockwise — increase result from 513 to 1023
    else if (result > (unsigned int)(1023 * 0.5) + sense) // if ADC value is greater than middle-tolerance, but not 1023, then it moves clockwise at a changing speed (increase or decrease)
    {
        setMotorDirection(1);                                        // set direction to clockwise
        OCR3A = (result - ((unsigned int)(1023 * 0.5) + sense)) * 2; // increase speed as input moves further from midpoint
    }
}
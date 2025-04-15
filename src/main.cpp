// Authors: I MADE KENT ABIATAR WIRANATHA, ANDREW LIEMARTA, BARI FAKHRUDIN, CHARLES AGUSTIN
// Net ID: kentabiatar,andrewliemarta,barifakhrudin,charlesagustin
// Date: 25-Mar-2025
// Assignment: Lab 4
//----------------------------------------------------------------------//
#include <avr/io.h>
#include "Arduino.h"
#include <avr/interrupt.h>
#include "Timer.h"
#include "ADC.h"
#include "PWM.h"
#include "SevenSegment.h"
#include "Switch.h"

volatile unsigned int current_amount = 9;

int main()
{
  // Initialize peripherals
  initTimer1(); // 10-sec countdown timer
  initTimer0(); // Debounce timer
  initPWMTimer3();
  initSwitch();
  initADC();
  initPWMPin();
  initSevenSegmentPin();
  sei();

  while (1)
  {

    uint16_t adc_value = readADC();                  // Read potentiometer
    MotorState motor = GetMotorDirection(adc_value); // get the motor state from based on the potentiometer input
    changeDutyCycle(motor, adc_value);               // change the duty cycle accordingly
  }

  return 0;
}

ISR(INT0_vect)
{
  delayMs(50);              // debounce the button
  changeDutyCycle(STOP, 0); // stop the motor
  countdown();              // do the seven segment countdown
}
// Authors: I MADE KENT ABIATAR WIRANATHA, ANDREW LIEMARTA, BARI FAKHRUDIN, CHARLES AGUSTIN
// Net ID: ,charlesagustin
// Date: 25-Mar-2025
// Assignment: Lab 4
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "ADC.h"
#include "PWM.h"
#include "SevenSegment.h"
#include "Switch.h"

enum state
{
  wait_pressed,
  wait_released
};
enum MotorState
{
  RUNNING,
  STOPPED
};
volatile enum MotorState motorState = RUNNING;

volatile int current_state = wait_pressed;
volatile unsigned int current_amount = 9;

int main()
{
  // Initialize peripherals
  initSwitch();
  initTimer0(); // Debounce timer
  initTimer1(); // 10-sec countdown timer
  initADC();
  initPWMPin();
  initPWMTimer3();
  initSevenSegmentPin();

  sei();

  while (1)
  {
    if (current_state != wait_pressed)
    {
      current_state = wait_pressed;
      delayMs(50);
    }

    unsigned int adc_value = readADC(); // Read potentiometer
    if (motorState == RUNNING)
    {
      changeDutyCycle(adc_value);
    }
    else
    {
      changeDutyCycle(0); // Stop motor (duty = 0%)
    }
  }

  return 0;
}

ISR(INT0_vect)
{
  current_state = wait_released;
  delayMs(50);
  PORTC = ~(PORTC); // ganti dengan function nyalain seven segment
}
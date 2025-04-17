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

enum ButtonState // states of the button for debounceing the button
{
  Wait_press,
  Debounce_press,
  Wait_release,
  Debounce_release
};

volatile ButtonState currentState = Wait_press; // initial button condition
int main()
{
  // Initialize peripherals
  initTimer1();    // 10-sec countdown timer
  initTimer0();    // Debounce timer
  initPWMTimer3(); // PWM
  initSwitch();
  initADC();
  initPWMPin();
  initSevenSegmentPin();
  sei(); // enable global interrupt

  while (1)
  {
    switch (currentState) // after interrupt is resolved, check the button state whether it is a debounce_press or debounce release
    {
    case Debounce_press: // if the button state is debounce_press (eg. the button just got pressed), then change the button state to wait_release and give a 50 milisecond delay to eliminate debounce effect
      delayMs(50);
      currentState = Wait_release;
      break;

    case Debounce_release: // if the state is debounce_release (eg. the button just got released), then change the button state to wait_press (reset the button state) and give a 50 milisecond delay to eliminate debounce effect
      delayMs(50);
      cli();                  // disable the global interrupt so it doesn't mess with the timing
      changeDutyCycle(511.5); // stop the motor
      countdown();            // do the seven segment countdown
      sei();                  // reenable the global interrupt
      currentState = Wait_press;
      break;
    }

    unsigned int adc_value = readADC(); // Read potentiometer
    changeDutyCycle(adc_value);         // change the duty cycle accordingly
  }

  return 0;
}

ISR(INT0_vect)
{
  if (currentState == Wait_press)
  {
    currentState = Debounce_press;
  }
  else if (currentState == Wait_release)
  {
    currentState = Debounce_release;
  }
}
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

volatile int current_state = wait_pressed;
volatile unsigned int current_amount = 9;

int main()
{
  // Initialize peripherals
  initSwitch();
  initTimer0(); // Debounce timer
  initTimer1(); // 10-sec countdown timer
  initADC();
  sei();
  initPWMPin();
  initPWMTimer3();
  initSevenSegmentPin();

  while (1)
  {
    if (current_state != wait_pressed)
    {
      current_state = wait_pressed;
      delayMs(50);
    }

    unsigned int adc_value = readADC(); // Read potentiometer
    changeDutyCycle(adc_value);
  }

  return 0;
}

ISR(INT0_vect)
{
  current_state = wait_released;
  delayMs(50);
  PORTC = 0xFF; // ganti dengan function nyalain seven segment
}
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "ADC.h"
#include "PWM.h"
#include "SevenSegment.h"

enum state
{
  wait_pressed,
  debounced_pressed,
  wait_released,
  debounced_released
};

volatile int current_state = wait_pressed;
volatile unsigned int current_amount = 9;

void initExternalInterrupt()
{
  DDRD &= ~(1 << DDD0);
  PORTD |= (1<<PORTD0);
  EICRA |= (1 << ISC00);  // Any logical change triggers INT0
  EICRA &= ~(1 << ISC01); // (ISC01 = 0, ISC00 = 1 → Any change)

  EIMSK |= (1 << INT0); // Enable INT0 interrupt
                  // Enable global interrupts
}

int main()
{
  // Initialize peripherals
  initExternalInterrupt();
  initTimer0(); // Debounce timer
  initTimer1(); // 10-sec countdown timer
  initADC();
  sei();
  initPWMPin();
  initPWMTimer3();
  initSevenSegmentPin();

  while (1)
  {
    unsigned int adc_value = readADC(); // Read potentiometer
    changeDutyCycle(adc_value);
  }

  return 0;
}

ISR(INT0_vect)
{
  PORTC = 0xFF;
}
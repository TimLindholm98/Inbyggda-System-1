#define F_CPU 16000000UL
#define LED (1 << PB0)

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include "serial.h"

void wait(uint32_t mSec){
  _delay_ms(mSec);
}

void LEDloop(uint32_t mSec){
  while(true){
    PORTB = LED;
    wait(mSec);
    PORTB = ~LED;
    wait(mSec);
  }
}
void LEDloop2(uint32_t mSec){
  while(true){
    PORTB = (1 << 0);
    wait(mSec);
    PORTB = ~(1 << 0);
    wait(mSec);
  }
}

void main (void) {
  DDRB &= ~(1<<PB0); //PORTBIT0 == OUTPUT

  LEDloop(500);
  LEDloop2(500);
}

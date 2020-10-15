#define F_CPU 16000000UL
#define LED (1 << PB0)

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include "serial.h"

void wait(uint32_t mSec){
  int i;
  for (i = 0; i < (mSec / 10); i++){
      _delay_ms(10);
  }
}

void LEDloop(int mSec){
  while(true){
    PORTB = LED;
    wait(mSec);
    PORTB = ~LED;
    wait(mSec);
  }
}
void LEDloop2(uint32_t mSec){
  while(true){
    PORTB = (1 << PB0);
    wait(mSec);
    PORTB = ~(1 << PB0);
    wait(mSec);
  }
}

int main (void) {
  //DDRB &= ~(1<<PB0); //PORTBIT0 == OUTPUT
  LEDloop(500);
  return 1;
}

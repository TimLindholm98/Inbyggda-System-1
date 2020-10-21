#define LED (1 << PB0)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "functions.h"

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
void LEDloop2(uint32_t mSec, char color){
  while(true){
    if(color == 'G'){
      PORTB = (1 << PB1);
      wait(mSec);
      PORTB ^= (1 << PB1);
      wait(mSec);
    }
    if(color == 'B'){
      PORTB ^= (1 << PB2);
      wait(mSec);
    }
    if(color == 'R'){
      PORTB = (1 << PB3);
      wait(mSec);
      PORTB ^= (1 << PB3);
      wait(mSec);
    }

  }
}

int ArrayLenght(char *pointer){
   int count = 0;
   while (*pointer != '\0') {
      count++;
      pointer++;
   }
   return count;
}

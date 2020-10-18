#define F_OSC 16000000UL

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include <string.h>
#include "serial.h"
#include "functions.h"

void main(void){
  uart_init();
  /*init_millis(F_OSC);
  sei();*/
  static unsigned long current_millis = 0;

  while(1){

    char myName[] = "TimLindholm\n";
    uart_putstr(myName);
    wait(1000);
  }
}

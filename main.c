#define F_OSC 16000000UL

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include <string.h>
#include "serial.h"
#include "functions.h"

void main(void){
  uart_init();

  while(1){
    uart_echo();
  }
}

#define F_OSC 16000000UL
#define MAX_BUFF 10

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include <string.h>
#include <util/atomic.h>
#include "serial.h"
#include "functions.h"

static char buffer_array[MAX_BUFF] = "";
static int indexing = 0;

void main(void){
  uart_init();
  sei();
  while(1){
    look_for_state(&buffer_array);
  }
}

ISR(USART_RX_vect){
  if(indexing == MAX_BUFF){
    indexing = 0;
  }
  else{
    while(!(UCSR0A & (1<<UDRE0)));
    buffer_array[indexing] = UDR0;
    indexing++;
  }
}

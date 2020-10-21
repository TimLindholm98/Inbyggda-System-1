#define F_OSC 16000000UL
#define MAX_BUFF 5

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h>
#include <ctype.h>
#include <util/atomic.h>
#include <string.h>
#include "serial.h"
#include "functions.h"

static volatile char buffer_array[MAX_BUFF] = "";
static int indexing = 0;

const char ON_STATE[] = "ON";
const char OFF_STATE[] = "OFF";

void main(void){
  uart_init();
  sei();
  while(1){
    //uart_putstr(buffer_array);
  }
}

ISR(USART_RX_vect){
    buffer_array[indexing] = UDR0;
    indexing++;
}

ISR(USART_UDRE_vect){
  buffer_array[4] = '\0';
  if(strncmp(buffer_array, OFF_STATE, 3) == 0){
    PORTB &= ~(1 << PB1);
  }
  buffer_array[3] = '\0';
  if(strncmp(buffer_array, ON_STATE, 3) == 0){
    PORTB |= (1 << PB1);
  }
  buffer_array[] = '\0 //MEMSET
}

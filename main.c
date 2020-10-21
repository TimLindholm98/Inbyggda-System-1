#define F_OSC 16000000UL
#define MAX_BUFF 10

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h>
#include <ctype.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <string.h>
#include "serial.h"
#include "functions.h"

static volatile char buffer_array[MAX_BUFF] = "";
volatile int indexing = 0;

const char ON_STATE[] = "ON";
const char OFF_STATE[] = "OFF";
volatile bool clear_buffer = 0;

void main(void){
  uart_init();
  sei();
  //PORTB |= (1 << PB1);
  while(1){
    if(clear_buffer == true){
      for(int i = 0; i < MAX_BUFF; i++){
        buffer_array[i] = 'F';
      }
      clear_buffer = false;
      //PORTB |= (1 << PB2);
    }
    else if(indexing > 2){
      uart_putstr(buffer_array);
      buffer_array[3] = '\n';
      buffer_array[4] = '\0';
      if(strncmp(buffer_array, OFF_STATE, 3) == 0){
        PORTB &= ~(1 << PB1);
        clear_buffer = true;
        indexing = 0;

      }
      buffer_array[2] = '\n';
      buffer_array[3] = '\0';
      if(strncmp(buffer_array, ON_STATE, 2) == 0){
        PORTB |= (1 << PB1);
        clear_buffer = true;
        indexing = 0;
      }
    }
  }
}

ISR(USART_RX_vect){
  int i = indexing;
  buffer_array[i] = uart_getchar();
  indexing++;
}

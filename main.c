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

static char buffer_array[MAX_BUFF] = "";
static volatile int indexing = 0;

const char ON_STATE[] = "ON";
const char OFF_STATE[] = "OFF";
volatile bool clear_buffer = 0;

void main(void){
  uart_init();
  sei();
  while(1){
    if(clear_buffer == true){
      for(int i = 0; i < MAX_BUFF-1; i++){
        buffer_array[i] = 'X';
      }
      buffer_array[MAX_BUFF] = '\0';
      clear_buffer = false;
      indexing = 0;
    }
    else{
      if(strstr(buffer_array,ON_STATE)){
        buffer_array[2] = '\n';
        buffer_array[3] = '\0';
        uart_putstr(buffer_array);  // echo back
        if(strncmp(buffer_array, ON_STATE, 2) == 0){
          PORTB |= (1 << PB1);
          clear_buffer = true;
          indexing = 0;
        }
      }
      else if(strstr(buffer_array,OFF_STATE)){
        buffer_array[3] = '\n';
        buffer_array[4] = '\0';
        uart_putstr(buffer_array);  // echo back
        if(strncmp(buffer_array, OFF_STATE, 3) == 0){
          PORTB &= ~(1 << PB1);
          clear_buffer = true;
          indexing = 0;
        }
      }
    }
  }
}

ISR(USART_RX_vect){

  if(indexing == MAX_BUFF){
    indexing = 0;
    buffer_array[indexing] = uart_getchar();
  }
  else{
    buffer_array[indexing] = uart_getchar();
    indexing++;
  }


}

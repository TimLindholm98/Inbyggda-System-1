#define f_osc 16000000UL
#define baudrate 38400
#define baud_prescaler f_osc/(16*baudrate)-1

#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void uart_init(void){
  // Set Baudrate
  UBRR0H = (uint8_t)(baud_prescaler>>8);
  UBRR0L = (uint8_t)(baud_prescaler);

  UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // Flyttar bit 1, 3 steg
  UCSR0C = (3<<UCSZ00); // Flyttar talet 3(011) i binärt ett steg så UCSZ00 och UCSZ01 är båda 1:or.
}

void uart_putchar(char chr){
  char char_to_send[] = {chr,'\r','\n'};
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = char_to_send++;
}

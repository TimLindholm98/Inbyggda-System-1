/*#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection
#define DISABLED    (0<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection*/

#define F_OSC 16000000UL
#define BAUDRATE 38400
#define BAUD_PRESCALER ((F_OSC / (BAUDRATE * 16UL))) - 1
#define MAX_BUFF 10

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "functions.h"


void uart_init(void){
  // Set Baudrate
  UBRR0H = (BAUD_PRESCALER>>8);
  UBRR0L = BAUD_PRESCALER;

  UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // Flyttar bit 1, 3 steg
  UCSR0C = (3<<UCSZ00); // Flyttar talet 3 i binärt ett steg så UCSZ00 och UCSZ01 är båda 1:or.

  UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve complete interrupt
  //UCSR0B |= (1 << TXCIE0); // Enable the USART Transmit complete interrupt

}

void uart_putchar(char c){
  if(c == '\n'){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = '\r';
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;

  }
  else{
    while(!(UCSR0A & (1<<UDRE0))); // Oändlig loop tills UDR0 är tom igen
    UDR0 = c;
  }
}

void uart_putstr(const char *string){
  while(*string != '\0'){
    uart_putchar(*string);
    string++;
  }
}

char uart_getchar(void){
  //while(!(UCSR0A & (1<<RXC0)));     //Behövs inte när vi har interrupts
  return UDR0;
}

void uart_echo(void){
  char received_value = uart_getchar();
  if(received_value != '\0'){
    uart_putchar(received_value);
  }
}

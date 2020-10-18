#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include <string.h>
#include "serial.h"
#include "functions.h"

void main(void){
  uart_init();

  while(1){
    char myName[] = "TimLindholm\n";
    uart_putstr(myName);
    wait(1000);
  }
}

#include <avr/io.h>
#include <stdbool.h> // while(true)
#include <util/delay.h> // For delay
#include "serial.h"
#include "functions.h"

int main(void){

  uart_init();
  while(1){
    uart_putchar('R');
    wait(250);
  }
  return 1;
}

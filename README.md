# Inbyggda-System-1



## Deluppgift 1: Blinka LED

### 1. Läs databladen för tillhandahållen LED och resistorer och räkna ut en lämplig resistorstorlek
   Kollade i PDF 1671493-LED.PDF
      Såg raden och använde detta för att räkna:
      
      Parameter = Forward Voltage, Typical = 2.1, IF = 20mA.      
      5 − 2.1 = 2.9
      2.9÷0.02 = 145
      
   Svar: runt 145 ohms motstånd.

### 3. 
  PB0
  ![alt text](https://i.imgur.com/gU3xKbO.png)
  
### 5.
Jag har använt arduino skölden från förra uppgiften för projektet, därför jag har kod för 'G' == green.
```C
    void LEDloop2(uint32_t mSec, char color){
     while(true){
      if(color == 'G'){
        PORTB ^= (1 << PB1);
        wait(mSec);
      }
      if(color == 'B'){
        PORTB ^= (1 << PB2);
        wait(mSec);
      }
      if(color == 'R'){
        PORTB ^= (1 << PB3);
        wait(mSec);
        }
      }
    }
```
## Deluppgift 2: Konfigurera upp UART för sändning (TX)
### 1. Implementera funktionen uart_init så att den konfigurerar upp USART0 för sändning (TX) enligt 8N1 i 38400 baud.
```C
    void uart_init(void){
  // Set Baudrate
  UBRR0H = (BAUD_PRESCALER>>8);
  UBRR0L = BAUD_PRESCALER;

  UCSR0B |= (1<<RXEN0)|(1<<TXEN0); //Både för transmit och recive för tydlighet.
  UCSR0C = (3<<UCSZ00); 

}
```
### 2. Implementera funktionen uart_putchar så att den skickar ett enskilt tecken över USART0, och lägger till tecknet ’\r’ (radretur) om tecknet vi vill skicka är ’\n’ (radbrytning).
```C
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
```
### 4 + 5. Implementera funktionen uart_putstr så att den med hjälp av uart_putchar skriver ut en hel sträng på serieterminalen.
```C
void main(void){
  while(1){
    uart_putstr("Tim Lindholm\n");
    wait(500);
  }
}

//----------

void uart_putstr(const char *string){
  while(*string != '\0'){
    uart_putchar(*string);
    string++;
  }
}
```
![alt text](https://i.imgur.com/4jgbJ5w.png)

## Deluppgift 3: Konfigurera upp UART för mottagning (RX)
### 1. Ändra implementationen av uart_init så att den även medger mottagning (RX).
```C
    UCSR0B |= **(1<<RXEN0)**|(1<<TXEN0);
```
```C

```
   **(1<<RXEN0)**
### 2. Implementera funktionen uart_getchar så att den tar emot ett enskilt tecken.
```C
char uart_getchar(void){
  while(!(UCSR0A & (1<<RXC0)));     //Behövs inte när vi har interrupts
  return UDR0;
}
```
### 3. Visa att funktionen fungerar genom att implementera uart_echo så att den väntar på ett inkommande tecken med hjälp av uart_getchar, och direkt skickar tillbaka samma tecken med uart_putchar. Anropa funktionen från main.
```C
void main(void){
  uart_init();
  while(1){
   uart_echo();
  }
}

//---------

void uart_echo(void){
  char received_value = uart_getchar();
  if(received_value != '\0'){
    uart_putchar(received_value);
  }
}
```
## Deluppgift 4 (VG-krav): Styr LED via UART

Koden för det här finns i mappen och är den jag har zipat och lämnat in.
Det jag inte hunnit lösa är felhantering om du skickar t.ex något ord som inte är "ON" eller "OFF". Men ska försöka lösa det, jag har en aning om att indexing skapar det.
Men det funkar att skicka med eller utan kontroll tecken.
```C
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
```

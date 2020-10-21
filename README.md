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
```C
    
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

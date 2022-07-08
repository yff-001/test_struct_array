#include <avr/io.h>

#include "uart.h"

#define BAUD        1000000
#define UBRR_REG    ((F_CPU)/(BAUD*8UL)-1)      // see spec sheet: buad rate generator        

void uart0_init() {
    UBRR0L = (uint8_t)UBRR_REG;                 // write lower byte
    UBRR0H = (uint8_t)(UBRR_REG >> 8);          // write higher byte

    UCSR0A |= (1<<U2X0);                        // U2X0 bit seems to be 1 by default on Pro Mini 3.3V 8Mhz
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // enable transmitter & receiver
    UCSR0B |= (1 << RXCIE0);                    // enable receive complete interrupt
}

void uart0_transmit(uint8_t data) {
    while (!(UCSR0A & (1<<UDRE0)));             // wait for empty transmit buffer
    UDR0 = data;                                // put data into buffer
}

void uart0_puts(char* message) {
    char* p = message;
    while (*p) {
        uart0_transmit(*p++);
    }
}
void uart3_init() {
    UBRR3L = (uint8_t)UBRR_REG;                 // write lower byte
    UBRR3H = (uint8_t)(UBRR_REG >> 8);          // write higher byte

    UCSR3A |= (1<<U2X3);                        // U2X0 bit seems to be 1 by default on Pro Mini 3.3V 8Mhz
    UCSR3B |= (1 << RXEN3) | (1 << TXEN3);      // enable transmitter & receiver
}

void uart3_transmit(uint8_t data) {
    while (!(UCSR3A & (1<<UDRE3)));             // wait for empty transmit buffer
    UDR3 = data;                                // put data into buffer
}
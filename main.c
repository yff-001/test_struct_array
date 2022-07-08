#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "uart.h"
#include "math.h"

#define DELAY_MS    1000

struct test_point_t {
    uint8_t adc_channel;
    char* message;
};

volatile uint8_t temp = 0;

int main() {
    DDRB |= (1<<PB7);
    // PORTB |= (1<<PB7);
    // adc_init();
    uart0_init();
    uart0_puts("uart0 initialized.\r\n");

    set_sleep_mode(0);

    sei();

    struct test_point_t x[] = {
        {0, "RTC"},
        {1, "ETC1"},
        {2, "ETC2"}
    };

    for(;;) {

        sleep_mode();
    }

}

ISR(USART0_RX_vect) {
    temp = UDR0;
}
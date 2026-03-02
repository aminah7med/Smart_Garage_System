#include "ultrasonic.h"

#define TRIG PD2
#define ECHO PD3

void init_ultrasonic() {
    DDRD |= (1 << TRIG);
    DDRD &= ~(1 << ECHO);
}

uint16_t measure_distance() {
    uint16_t count = 0;

    PORTD &= ~(1 << TRIG);
    _delay_us(2);

    PORTD |= (1 << TRIG);
    _delay_us(10);
    PORTD &= ~(1 << TRIG);

    while (!(PIND & (1 << ECHO)));
    while (PIND & (1 << ECHO)) {
        count++;
        _delay_us(1);
        if (count > 30000) break;
    }

    return count / 58;
}
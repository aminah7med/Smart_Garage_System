#include "servo.h"

#define SERVO_PIN PD5

void init_servo() {
    DDRD |= (1 << SERVO_PIN);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
    ICR1 = 19999;
}

void move_servo(uint16_t angle) {
    uint16_t ocr_value = (angle * 11) + 500;
    OCR1A = ocr_value;
}
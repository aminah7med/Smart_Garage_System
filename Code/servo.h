#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

void init_servo(void);
void move_servo(uint16_t angle);

#endif
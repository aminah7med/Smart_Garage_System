#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <avr/io.h>
#include <util/delay.h>

void init_ultrasonic(void);
uint16_t measure_distance(void);

#endif
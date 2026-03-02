#ifndef GAS_SENSOR_H_
#define GAS_SENSOR_H_

#include <avr/io.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#define GAS_SENSOR_CHANNEL 7

#endif
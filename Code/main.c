#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"
#include "ultrasonic.h"
#include "servo.h"
#include "gas_sensor.h"

#define BUZZER_PORT PORTC
#define BUZZER_DDR DDRC
#define BUZZER_PIN PC0

#define LED_PORT PORTC
#define LED_DDR DDRC
#define LED_PIN PC1

int main(void) {

    BUZZER_DDR |= (1 << BUZZER_PIN);
    LED_DDR |= (1 << LED_PIN);

    LCD_init();
    ADC_Init();
    init_ultrasonic();
    init_servo();

    LCD_clear();
    LCD_send_string("WELCOME");
    move_servo(90);
    _delay_ms(500);

    uint16_t gas_value, distance;
    uint8_t action_triggered = 0;

    while (1) {

        gas_value = ADC_Read(GAS_SENSOR_CHANNEL);

        char buffer[16];
        itoa(gas_value, buffer, 10);

        LCD_clear();

        if (gas_value > 80) {
            LCD_send_command(0x80);
            LCD_send_string("WARNING!");
            BUZZER_PORT |= (1 << BUZZER_PIN);
            _delay_ms(300);
            BUZZER_PORT &= ~(1 << BUZZER_PIN);
        } else {
            LCD_send_command(0x80);
            LCD_send_string("SAFE");
            BUZZER_PORT &= ~(1 << BUZZER_PIN);
        }

        LCD_send_command(0xC0);
        LCD_send_string("GAS: ");
        LCD_send_string(buffer);

        distance = measure_distance();

        if (distance <= 15 && action_triggered == 0 && gas_value <= 80) {

            LCD_clear();
            LCD_send_string("WELCOME GUEST");

            LED_PORT |= (1 << LED_PIN);

            move_servo(160);
            _delay_ms(800);
            move_servo(90);

            LED_PORT &= ~(1 << LED_PIN);

            action_triggered = 1;
        }
        else if (distance > 15) {
            action_triggered = 0;
        }

        _delay_ms(100);
    }
}
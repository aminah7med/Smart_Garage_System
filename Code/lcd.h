#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

void LCD_init(void);
void LCD_send_command(unsigned char cmd);
void LCD_send_char(unsigned char data);
void LCD_send_string(const char *str);
void LCD_clear(void);

#endif
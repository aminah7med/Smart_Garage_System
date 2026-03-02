#include "lcd.h"

#define LCD_DDR DDRA
#define LCD_PORT PORTA
#define RS PA1
#define E PA2

void LCD_enable_pulse(void);
void LCD_send_4bits(unsigned char data);

void LCD_init(void)
{
    LCD_DDR = 0xFE;
    LCD_PORT = 0x00;
    _delay_ms(20);
    LCD_send_command(0x33);
    LCD_send_command(0x32);
    LCD_send_command(0x28);
    LCD_send_command(0x0C);
    LCD_send_command(0x06);
    LCD_send_command(0x01);
    _delay_ms(2);
}

void LCD_clear()
{
    LCD_send_command(0x01);
    _delay_ms(2);
}

void LCD_send_command(unsigned char cmd)
{
    LCD_PORT &= ~(1 << RS);
    LCD_send_4bits(cmd >> 4);
    LCD_send_4bits(cmd & 0x0F);
}

void LCD_send_char(unsigned char data)
{
    LCD_PORT |= (1 << RS);
    LCD_send_4bits(data >> 4);
    LCD_send_4bits(data & 0x0F);
}

void LCD_send_4bits(unsigned char data)
{
    LCD_PORT = (LCD_PORT & 0x87) | (data << 3);
    LCD_enable_pulse();
}

void LCD_enable_pulse(void)
{
    LCD_PORT |= (1 << E);
    _delay_us(1);
    LCD_PORT &= ~(1 << E);
    _delay_us(100);
}

void LCD_send_string(const char *str)
{
    while (*str)
    {
        LCD_send_char(*str++);
    }
}
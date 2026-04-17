#include "lcd.h"
#include "temporizador.h"

void lcd_pulseEnable(void)
{
    PORTD |= (1 << LCD_E);
    while(obtener_millis() < 1);
    PORTD &= ~(1 << LCD_E);
    while(obtener_millis() < 1);
}

void lcd_write4bits(uint8_t data)
{
    PORTD &= ~((1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4));

    if (data & 0x08) PORTD |= (1<<LCD_D7);
    if (data & 0x04) PORTD |= (1<<LCD_D6);
    if (data & 0x02) PORTD |= (1<<LCD_D5);
    if (data & 0x01) PORTD |= (1<<LCD_D4);

    lcd_pulseEnable();
}

void lcd_send(uint8_t value, uint8_t mode)
{
    if (mode)
        PORTB |= (1<<LCD_RS);   // DATA
    else
        PORTB &= ~(1<<LCD_RS);  // COMMAND

    PORTB &= ~(1<<LCD_RW); // WRITE

    lcd_write4bits(value >> 4);
    lcd_write4bits(value & 0x0F);

    while(obtener_millis() < 2);
}

/// funciones a llamar

void lcd_begin(void)
{
    DDRD |= (1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4)|(1<<LCD_E);
    DDRB |= (1<<LCD_RS)|(1<<LCD_RW);

    while(obtener_millis() < 50);

    lcd_write4bits(0x03);
    while(obtener_millis() < 1);
    lcd_write4bits(0x03);
    while(obtener_millis() < 1);
    lcd_write4bits(0x03);
    lcd_write4bits(0x02);

    lcd_send(0x28, 0); // 4 bits, 2 líneas
    lcd_send(0x0C, 0); // display ON
    lcd_send(0x06, 0); // cursor move
    lcd_send(0x01, 0); // clear

    while(obtener_millis() < 2);
}

void lcd_clear(void)
{
    lcd_send(0x01, 0);
    while(obtener_millis() < 2);
}

void lcd_setCursor(uint8_t col, uint8_t row)
{
    uint8_t address;

    if (row == 0)
        address = 0x00 + col;
    else
        address = 0x40 + col;

    lcd_send(0x80 | address, 0);
}

void lcd_print(const char *str)
{
    while (*str)
    {
        lcd_send(*str++, 1);
    }
}

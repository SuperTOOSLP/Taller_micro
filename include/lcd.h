#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <temporizador.h>

/// asignacion de pines para lcd
#define LCD_D7 PD2
#define LCD_D6 PD3
#define LCD_D5 PD4
#define LCD_D4 PD5
#define LCD_E  PD6
#define LCD_RS PB4
#define LCD_RW PB5

void lcd_begin(void);
void lcd_clear(void);
void lcd_setCursor(uint8_t col, uint8_t row);
void lcd_print(const char *str);

#endif
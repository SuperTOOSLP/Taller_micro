#include "lcd.h"

void lcd_pulseEnable(void)
{
    PORTD |= (1 << LCD_E);

    uint32_t t0 = obtener_millis();
    while ((obtener_millis() - t0) < 1);

    PORTD &= ~(1 << LCD_E);

    t0 = obtener_millis();
    while ((obtener_millis() - t0) < 1);
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

    uint32_t t0 = obtener_millis();
    while ((obtener_millis() - t0) < 2);
}

/// funciones a llamar

void lcd_begin(void)
{
    DDRD |= (1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4)|(1<<LCD_E);
    DDRB |= (1<<LCD_RS)|(1<<LCD_RW);

    uint32_t t0 = obtener_millis();
    while ((obtener_millis() - t0) < 50);

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

void mostrar_display(void){
    obtener_tiempo();

    char buffer_distancia[10];
    char buffer_hora[4];
    char buffer_minutos[4];
    char buffer_segundos[4];
    char buffer_temperatura[10];


    sprintf(buffer_distancia, "%d cm", (int)obtener_distancia());
    sprintf(buffer_temperatura, "%d", (int)read_temperature());
    sprintf(buffer_hora, "%.2d:", (int)h);
    sprintf(buffer_minutos, "%.2d:", (int)m);
    sprintf(buffer_segundos, "%.2d", (int)s);

    lcd_clear();
    /// x y

    lcd_setCursor(0, 0);
    lcd_print(buffer_hora);

    lcd_setCursor(3, 0);
    lcd_print(buffer_minutos);

    lcd_setCursor(6, 0);
    lcd_print(buffer_segundos);

    lcd_setCursor(10, 0);
    lcd_print(buffer_distancia);

    lcd_setCursor(0, 1);
    lcd_print(buffer_temperatura);
    
}

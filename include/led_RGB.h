#ifndef LED_RGB_H
#define LED_RGB_H

#include <avr/io.h>

void led_RGB_init(void);
void led_RGB(int r, int g, int b);

#endif
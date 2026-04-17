#include "led_RGB.h"

/// funcion donde se van a meter los valores de 0 a 255

void led_RGB_init(void){
    DDRB |= (1<<PB3) | (1<<PB2) | (1<<PB1);
    PORTB &= ~((1<<PB3) | (1<<PB2) | (1<<PB1));
}

void led_RGB(int r, int g, int b){

}
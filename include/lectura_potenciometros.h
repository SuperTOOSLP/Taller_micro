#ifndef LECTURA_POTENCIOMETROS_H
#define LECTURA_POTENCIOMETROS_H

#include<avr/io.h>
#include<stdint.h>

uint16_t leer_pot1(void); // A1
uint16_t leer_pot2(void); // A2
uint16_t leer_pot3(void); // A3

void iniciar_lectura_potenciometros(void);

#endif
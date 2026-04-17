#ifndef TIEMPO_H
#define TIEMPO_H

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t h, m, s;

void iniciar_tiempo(void);
void obtener_tiempo(uint8_t *h, uint8_t *m, uint8_t *s);

#endif

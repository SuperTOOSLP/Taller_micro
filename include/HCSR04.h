#ifndef HCSR04_H
#define HCSR04_H

#include<avr/io.h>
#include "temporizador.h"

// Pines
#define TRIG PD7
#define ECHO PB0

void distancia_init(void);
float obtener_distancia(void);

#endif
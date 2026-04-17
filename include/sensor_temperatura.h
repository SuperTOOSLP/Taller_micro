#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include <avr/io.h>

void adc_init(void);
float read_temperature(void);

#endif
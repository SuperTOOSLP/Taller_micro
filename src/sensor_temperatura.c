#include "sensor_temperatura.h"

void adc_init(void)
{
    // Referencia AVcc (5V), canal inicial ADC0
    ADMUX = (1 << REFS0);

    // Habilitar ADC
    // Prescaler 128 → 16MHz / 128 = 125kHz (correcto)
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/// lectura del adc
uint16_t adc_read(uint8_t channel)
{
    // Limpiar canal anterior (mantener referencia)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Iniciar conversión
    ADCSRA |= (1 << ADSC);

    // Esperar fin
    while (ADCSRA & (1 << ADSC));

    return ADC; // 10 bits (0–1023)
}


float read_temperature(void)
{
    uint16_t adc_val = adc_read(0); // A0

    // Convertir a voltaje
    float voltage = (adc_val * 5.0) / 1023.0;

    float temperature = voltage * 100.0;

    return temperature;
}
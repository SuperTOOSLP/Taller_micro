#include "lectura_potenciometros.h"


void iniciar_lectura_potenciometros(void)
{
    // Referencia AVcc (5V)
    ADMUX = (1 << REFS0);

    // Habilitar ADC + prescaler 128
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}


static uint16_t leer_adc(uint8_t canal)
{
    // Seleccionar canal (A0–A7)
    ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

    // Iniciar conversión
    ADCSRA |= (1 << ADSC);

    // Esperar
    while (ADCSRA & (1 << ADSC));

    return ADC;
}

///lectura

uint16_t leer_pot1(void)
{
    return leer_adc(1); // A1
}

uint16_t leer_pot2(void)
{
    return leer_adc(2); // A2
}

uint16_t leer_pot3(void)
{
    return leer_adc(3); // A3
}
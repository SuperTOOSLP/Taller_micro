#include "hcsr04.h"


void distancia_init(void)
{
    DDRD |= (1 << TRIG);     // salida
    DDRB &= ~(1 << ECHO);    // entrada
}

// Pulso de disparo (~10us, aproximado con instrucciones)
static void trigger_pulso(void)
{
    PORTD &= ~(1 << TRIG);
    
    // pequeño tiempo
    for (volatile int i = 0; i < 10; i++);

    PORTD |= (1 << TRIG);

    // ~10us aproximado
    for (volatile int i = 0; i < 100; i++);

    PORTD &= ~(1 << TRIG);
}

float obtener_distancia(void)
{
    uint32_t timeout = obtener_millis();

    trigger_pulso();

    // Esperar subida con timeout
    while (!(PINB & (1 << ECHO)))
    {
        if ((obtener_millis() - timeout) > 50)
            return -1; // error
    }

    uint32_t t_inicio = obtener_millis();

    // Esperar bajada con timeout
    while (PINB & (1 << ECHO))
    {
        if ((obtener_millis() - t_inicio) > 50)
            return -1; // error
    }

    uint32_t t_fin = obtener_millis();

    float distancia = (t_fin - t_inicio) * 17.15;

    return distancia;
}
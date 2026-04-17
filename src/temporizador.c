#include "temporizador.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint32_t contador = 0;

void timer0_init(void)
{
    cli();

    TCCR0A = 0x00;

    // Prescaler 64 → ~1 ms
    TCCR0B = (1 << CS01) | (1 << CS00);

    TIMSK0 = (1 << TOIE0);

    sei();
}

uint32_t obtener_millis(void)
{
    uint32_t temp;

    cli();   
    temp = contador;
    sei();

    return temp;
}

ISR(TIMER0_OVF_vect)
{
    contador++;  // ~1 ms
}
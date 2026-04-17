#include "tiempo.h"

volatile uint8_t seg = 0, min = 0, hora = 0;

ISR(TIMER1_COMPA_vect){
    if(++seg == 60){ seg = 0;
        if(++min == 60){ min = 0;
            if(++hora == 24){ hora = 0;
            }
        }
    }
}

void iniciar_tiempo(void){
    //CTC, N = 1024 -> ISR casa 1 seg
    TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
    OCR1A = 15624; // 16E6/1024 - 1
    TIMSK1 = (1<<OCIE1A);
    sei();
}

void obtener_tiempo(uint8_t *h, uint8_t *m, uint8_t *s)
{
    cli();
    *h = hora;
    *m = min;
    *s = seg;
    sei();
}

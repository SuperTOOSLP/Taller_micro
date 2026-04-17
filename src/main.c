#include "lcd.h"
#include "led_RGB.h"
#include "temporizador.h"
#include "tiempo.h"
#include "lectura_potenciometros.h"
 
uint32_t tiempo = 0;
uint32_t pasado = 0;

int main(){

    timer0_init();  
    iniciar_tiempo();

    adc_init();
    iniciar_lectura_potenciometros();
    distancia_init();

    led_RGB_init();
    lcd_begin();

    lcd_setCursor(0, 0);
    lcd_print("Iniciando");

    while(1){
        
        tiempo = obtener_millis();
        uint32_t dt = tiempo - pasado;

        if(dt >= 1000){

            mostrar_display();

            pasado = tiempo;
        }
    }

    return 0;
}

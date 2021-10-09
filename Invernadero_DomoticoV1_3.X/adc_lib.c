
#include "adc_lib.h"
#include <xc.h>



void adc_init (){
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Analógica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisición 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversión Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificación Izquierda (modo-8bits).
    ADCON0bits.ADON = 1; //  Habilita el Módulo AD.
}



unsigned char adc_read(){
    ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
    while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
    return ADRESH; //  Lectura de valor AD    
}

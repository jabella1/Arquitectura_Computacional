#include <xc.h>
#include "Config.h"
#include "pinout.h"
#include "LCD.h"
#include "keypad.h"
#include "DHT11.h"
#include "Actuadores.h"
#include "Variables.h"



void main(){

    OSCCON=0x72;        //set internal oscillator with frequency 8 MHz*/
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */  

    ConfigurarPuertosLCD();
    initActuadores();
    LCD_Init();
    initTeclado();
    ApagarAspersores();
    ApagarVentiladores();
    ApagarLeds();
    
    while(1){   
     if(PrimeraVez==true){  
         PedirTodosLosDatos(Temperatura,Humedad,MargenErrorT,MargenErrorH);
         TemperaturaAdecuada = DatoDigitadoAEntero(Temperatura); 
         HumedadAdecuada = DatoDigitadoAEntero(Humedad);
         MargenET = MargenErrorT[0]-48;
         MargenEH = MargenErrorH[0]-48;
         PrimeraVez=false;
    }
        DatosSensorTH(Datos);
        Comparar_T_H_Adecuados(&Datos[0],&Datos[1],TemperaturaAdecuada,HumedadAdecuada,MargenET,MargenEH); 
        ControlHumedadAspersor(&Datos[1],HumedadAdecuada,MargenEH);
        ControlTemperaturaVentilador(&Datos[0],TemperaturaAdecuada,MargenET);
        
        MostrarHumedad(Cadena,Datos[1]);
    
        MostrarTemperatura(Cadena,Datos[0]);
       
       __delay_ms(500);
     }
}





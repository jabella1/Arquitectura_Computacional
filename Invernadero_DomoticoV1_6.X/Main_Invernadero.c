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
     if(indice<2){  
         PedirTodosLosDatos(Temperatura,Humedad,MargenErrorT,MargenErrorH);
         indice = 2;
    }else{
        if(bandera==false){
         TemperaturaAdecuada = DatoDigitadoAEntero(Temperatura); 
         HumedadAdecuada = DatoDigitadoAEntero(Humedad);
         MargenET = MargenErrorT[0]-48;
         MargenEH = MargenErrorH[0]-48;
        }
        bandera=true;
    }
     if (bandera==true){ 
        DatosSensorTH(Datos);
        Comparar_T_H_Adecuados(&Datos[0],&Datos[1],TemperaturaAdecuada,HumedadAdecuada,MargenET,MargenEH); 
        ControlHumedadAspersor(&Datos[1],HumedadAdecuada,MargenEH);
        ControlTemperaturaVentilador(&Datos[0],TemperaturaAdecuada,MargenET);
        
       /* convert humidity value to ascii and send it to display*/
        sprintf(Cadena,"%d",Datos[1]);
        LCD_String_xy(0,0,Cadena);
        sprintf(Cadena,".%d",0);
        LCD_Char('%');
        sprintf(Cadena,"  Hum.");
        LCD_String(Cadena);
    
       /* convert temperature value to ascii and send it to display*/
       sprintf(Cadena,"%d",Datos[0]);
       LCD_String_xy(2,0,Cadena);
       sprintf(Cadena,".%d",0);
       LCD_Char(0xdf);
       sprintf(Cadena,"C Temp.");
       LCD_String(Cadena);

       __delay_ms(500);
     }
    }
}





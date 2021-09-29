#include "Config.h"
#include "pinout.h"
#include <xc.h>
#include "LCD.h"
#include "keypad.h"
#include <pic18f4550.h>
#include <stdbool.h>

#define ON 1
#define OFF 0;
#define TemperaturaAdecuada true
#define HumedadAdecuada true


void PrenderLed();
void ImprimirTemperaturaAdecuada(char prmTemperatura[]);

void main(){
    bool bandera = false;
    
    unsigned char tecla;
    OSCCON = 0x70;
    Configuracion_Puertos_Leds = 0;
    
    unsigned char Temperatura[3];
    unsigned char indice = 0;
    
    RBPU=0;                             /* activate pull-up resistor */
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    LCD_String_xy(0,0,"Temp. Adecuada");
    LCD_Command(0xC0);                  /* display pressed key on 2nd line of LCD */
    while(1){
     if(indice<3){
     PrenderLed();
     tecla=keyfind();
     LCD_Char(tecla);
     Temperatura[indice] = tecla;
     indice++;
    }else{
       if(bandera==false){
       LCD_Clear();
       LCD_String_xy(0,0,"Temp. digitada:");
       LCD_Command(0xC0); 
       ImprimirTemperaturaAdecuada(Temperatura); 
       bandera=true;
       }
    }
    }
    
}

void PrenderLed(){
    if(TemperaturaAdecuada==false||HumedadAdecuada==false){
       Led_Amarillo=ON; 
    }else if(TemperaturaAdecuada==false && HumedadAdecuada==false){
        Led_Rojo=ON;
    }else{
        Led_Verde=ON;
    }
}

void ImprimirTemperaturaAdecuada(char prmTemperatura[]){
    for(int i = 0 ; i<3;i++){
      LCD_Char(prmTemperatura[i]); 
    }
}

#include "Config.h"
#include "pinout.h"
#include <xc.h>
#include "LCD.h"
#include "keypad.h"
#include <pic18f4550.h>
#include <stdbool.h>
#include <string.h>
#include "adc_lib.h"
#include "DHT11.h"

#define ON 1
#define OFF 0;

void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada);
int TemperaturaDigitada(unsigned char prmTemperatura[]);
void CompararTemperatura(char *TempActual,int TempDigitada);

void main(){
   
  
    Configuracion_Puertos_Leds = 0; //Configura el puerto de leds como salida
    LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
    TRISA=0xFF; //
    bool bandera = false;
    unsigned char tecla;
    unsigned char Temperatura[2];
    unsigned char indice = 0;
    int TemperaturaA=0;
    int TemperaturaAdecuada=0;
    char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
    char Checksum;
    
    OSCCON = 0x72;      /* set internal oscillator with frequency 8 MHz*/
    
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */  
    

     RBPU=0;                             /* activate pull-up resistor */
     LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
     LCD_String_xy(0,0,"Temp. Adecuada");
     LCD_Command(0xC0);  /* display pressed key on 2nd line of LCD */
   //  adc_init();
    while(1){
     if(indice<2){  
     tecla=keyfind();
     LCD_Char(tecla);
     Temperatura[indice] = tecla;
     indice++;
    }else{
        if(bandera==false){
         TemperaturaAdecuada = TemperaturaDigitada(Temperatura);    
        }
       bandera=true;
    }
     if (bandera==true){ 
         
         DHT11_Start();                  // send start pulse to DHT11 module */
         DHT11_CheckResponse();          // wait for response from DHT11 module */
    
     //read 40-bit data from DHT11 module 
         RH_Integral = DHT11_ReadData(); // read Relative Humidity's integral value 
         RH_Decimal = DHT11_ReadData();  // read Relative Humidity's decimal value 
         T_Integral = DHT11_ReadData();  // read Temperature's integral value 
         T_Decimal = DHT11_ReadData();   // read Relative Temperature's decimal value 
         Checksum = DHT11_ReadData();    // read 8-bit checksum value 
        
 
       CompararTemperatura(&T_Integral,TemperaturaAdecuada);
       __delay_ms(500);
     }
      
    
    }
    
}

void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada){
    Led_Amarillo=OFF;
    Led_Rojo=OFF;
    Led_Verde=OFF;
    if(TemperaturaAdecuada==false||HumedadAdecuada==false){
       Led_Amarillo=ON; 
    }else if(TemperaturaAdecuada==false && HumedadAdecuada==false){
        Led_Rojo=ON;
    }else{
        Led_Verde=ON;
    }
}

int TemperaturaDigitada(unsigned char prmTemperatura[]){
    int Decena = 0;
    int Unidad = 0;
    
    int Resultado=0;
    
    Decena = prmTemperatura[0]-'0';
    Unidad = prmTemperatura[1]-'0';
    
    Decena = Decena * 10;
    Resultado = Decena + Unidad;
    
    return Resultado;
}


void CompararTemperatura(char *TempActual,int TempDigitada){
    bool TemperaturaAdecuada= true;
    bool HumedadAdecuada =true;
    if(*TempActual<TempDigitada-2 || *TempActual >TempDigitada+2){
           TemperaturaAdecuada=false; 
           PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
        }else{
            PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
        }
}


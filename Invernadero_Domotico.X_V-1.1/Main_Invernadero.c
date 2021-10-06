#include "Config.h"
#include "pinout.h"
#include <xc.h>
#include "LCD.h"
#include "keypad.h"
#include <pic18f4550.h>
#include <stdbool.h>
#include <string.h>
#include "adc_lib.h"

#define ON 1
#define OFF 0;

void EstableciendoValorPines();
void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada);
void ImprimirTemperaturaAdecuada(char prmTemperatura[]);
int TemperaturaActual();
int TemperaturaDigitada(unsigned char prmTemperatura[]);
void CompararTemperatura(int TempActual,int TempDigitada);

void main(){
   //void EstableciendoValorPines(); //Inicializa puertos
   
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    //OSCCON=0x70;
    
    Configuracion_Puertos_Leds = 0; //Configura el puerto de leds como salida
    LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
    TRISA=0xFF; // Configura como entrada el pin 0 del puerto A para el sensor
                                        //temperatura 
    bool bandera = false;
    unsigned char tecla;
    unsigned char Temperatura[2];
    unsigned char indice = 0;
    int TemperaturaA=0;
    int TemperaturaAdecuada=0;
    

     RBPU=0;                             /* activate pull-up resistor */
     LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
     LCD_String_xy(0,0,"Temp. Adecuada");
     LCD_Command(0xC0);  /* display pressed key on 2nd line of LCD */
     adc_init();
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
         TemperaturaA=TemperaturaActual();
         CompararTemperatura(TemperaturaA,TemperaturaAdecuada);
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

int TemperaturaActual(){  
        unsigned int value_adc = 0;
        double temp = 0.0;
        ADCON0bits.GO_DONE = 1; //Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        return (int)temp;
}


void CompararTemperatura(int TempActual,int TempDigitada){
    bool TemperaturaAdecuada= true;
    bool HumedadAdecuada =true;
    if(TempActual<TempDigitada-2 || TempActual >TempDigitada+2){
           TemperaturaAdecuada=false; 
           PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
        }else{
            PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
        }
}

void EstableciendoValorPines(){
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    
    Configuracion_Puertos_Leds = 0; //Configura el puerto de leds como salida
    LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
    TRISA=0xFF; // Configura como entrada el pin 0 del puerto A para el sensor
                                        //temperatura
}

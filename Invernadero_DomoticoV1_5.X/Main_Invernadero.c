#include "Config.h"
#include "pinout.h"
#include <xc.h>
#include "LCD.h"
#include "keypad.h"
#include <pic18f4550.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "DHT11.h"

typedef char String[50];

#define ON 1
#define OFF 0

void ControlTemperaturaVentilador(char *TempActual,int TempDigitada,int MargenErrorT);
void ControlHumedadAspersor(char *HumedadActual,int HumedadDigitada,int MargenErrorH);
void PedirDato(String Etiqueta,unsigned char vecLlenar[],int CantDatos);
void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada);
int DatoDigitado(unsigned char prmTemperatura[]);
void Comparar_T_H_Adecuados(char *TempActual,char *HumActual,int TempDigitada,int HumDigitada,int MargenErrorT,int MargenErrorH);
void DatosSensorTH(char Datos[]);
void InicializarLeds();
void ApagarAspersores();
void ApagarVentiladores();

void main(){
   
  
    Configuracion_Puertos_Leds = 0; //Configura el puerto de leds como salida
    LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
    bool bandera = false;
    unsigned char Temperatura[2];
    unsigned char Humedad[2];
    unsigned char MargenErrorT[1];
    unsigned char MargenErrorH[1];
    int MargenET=0;
    int MargenEH=0;
    char Datos[2];
    char Cadena[10];
    int indice = 0;
    int TemperaturaAdecuada=0;
    int HumedadAdecuada=0;
  
    
    OSCCON = 0x72;      /* set internal oscillator with frequency 8 MHz*/
    
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */  
    Confi_AspersoresVentiladores=0x00;
    ApagarAspersores();
     ApagarVentiladores();
     RBPU=0;                             /* activate pull-up resistor */
     LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
     InicializarLeds();
    while(1){   
     if(indice<2){  
       PedirDato("Temp. Adecuada",Temperatura,2);
       __delay_ms(100);
       PedirDato("Mgn Error Temp",MargenErrorT,1);
        __delay_ms(100);
       PedirDato("Hum. Adecuada",Humedad,2);
       __delay_ms(100);
       PedirDato("Mgn Error Hum",MargenErrorH,1);
       indice = 2;
    }else{
        if(bandera==false){
         TemperaturaAdecuada = DatoDigitado(Temperatura); 
         HumedadAdecuada = DatoDigitado(Humedad);
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

       __delay_ms(800);
     }
      
    }
    
}

void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada){
    InicializarLeds();
    if(TemperaturaAdecuada==false && HumedadAdecuada==false){
       Led_Rojo=ON; 
    }else if(TemperaturaAdecuada==false || HumedadAdecuada==false){
        Led_Amarillo=ON;
    }else{
        Led_Verde=ON;
    }
}

int DatoDigitado(unsigned char prmTemperatura[]){
    int Decena = 0;
    int Unidad = 0;
    
    int Resultado=0;
    
    Decena = prmTemperatura[0]-'0';
    Unidad = prmTemperatura[1]-'0';
    
    Decena = Decena * 10;
    Resultado = Decena + Unidad;
    
    return Resultado;
}


void Comparar_T_H_Adecuados(char *TempActual,char *HumActual,int TempDigitada,
        int HumDigitada,int MargenErrorT,int MargenErrorH){
    bool TemperaturaAdecuada= true;
    bool HumedadAdecuada =true;
    if(*TempActual<TempDigitada-MargenErrorT || *TempActual >TempDigitada+MargenErrorT){
           TemperaturaAdecuada=false; 
    }
    if(*HumActual<HumDigitada-MargenErrorH || *HumActual>HumDigitada+MargenErrorH){
        HumedadAdecuada=false;
    }
    
   PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
}

void PedirDato(String Etiqueta,unsigned char vecLlenar[],int CantDatos){
     LCD_Clear();
     
     unsigned char tecla;
     LCD_String_xy(0,0,Etiqueta);
     LCD_Command(0xC0);  /* display pressed key on 2nd line of LCD */
     
     for(int i=0 ; i < CantDatos ; i++){
     tecla=keyfind();
     LCD_Char(tecla);
     vecLlenar[i] = tecla;
     }
     __delay_ms(100);
     LCD_Clear();
}

void DatosSensorTH(char Datos[]){
         char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
         char Checksum;
         DHT11_Start();                  // send start pulse to DHT11 module */
         DHT11_CheckResponse();          // wait for response from DHT11 module */
    
     //read 40-bit data from DHT11 module 
         RH_Integral = DHT11_ReadData(); // read Relative Humidity's integral value 
         RH_Decimal = DHT11_ReadData();  // read Relative Humidity's decimal value 
         T_Integral = DHT11_ReadData();  // read Temperature's integral value 
         T_Decimal = DHT11_ReadData();   // read Relative Temperature's decimal value 
         Checksum = DHT11_ReadData();    // read 8-bit checksum value
         
         Datos[0]=T_Integral;
         Datos[1]=RH_Integral;
}
void InicializarLeds(){
    Led_Amarillo=OFF;
    Led_Rojo=OFF;
    Led_Verde=OFF;
}
void ControlHumedadAspersor(char *HumedadActual,int HumedadDigitada,int MargenErrorH){
    if(*HumedadActual<HumedadDigitada-MargenErrorH){
        Aspersor1=ON;
        Aspersor2=ON;
    }else{
        //ApagarAspersores();
        Aspersor1=OFF;
        Aspersor2=OFF;
    }
}

void ControlTemperaturaVentilador(char *TempActual,int TempDigitada,int MargenErrorT){
    if(*TempActual>TempDigitada+MargenErrorT){
        Ventilador1=ON;
        Ventilador2=ON;
    }else{
        ApagarVentiladores();
    }
}
void ApagarAspersores(){
    Aspersor1=OFF;
    Aspersor2=OFF;
}
void ApagarVentiladores(){
    Ventilador1=OFF;
    Ventilador2=OFF;
}


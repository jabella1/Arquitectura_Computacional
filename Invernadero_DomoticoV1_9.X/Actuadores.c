

#include "Actuadores.h"
#include "pinout.h"

#define ON 1
#define OFF 0

bool VentiladoresEncendidosTemp=false;
bool VentiladoresEncendidosHum=false;
// Configura los puertos donde estan conectado los Aspersores, Ventiladores y Leds como salida.
void initActuadores(){
    Confi_AspersoresVentiladoresCalefactor=0x00;
    Configuracion_Puertos_Leds  = 0;
}

// Manda un valor de 0 el cual esta definido como constante en la variable OFF para 
//apagar los aspersores
void ApagarAspersores(){
    Aspersor1=OFF;
    Aspersor2=OFF;
}

// Manda un valor de 0 el cual esta definido como constante en la variable OFF
//para apagar los Ventiladores
void ApagarVentiladores(){
    Ventilador1=OFF;
    Ventilador2=OFF;
}
// Manda un valor de 0 el cual esta definido como constante en la variable OFF
//para apagar el Calefactor
void ApagarCalefactor(){
    Calefactor=OFF;
}

//Manda un valor de 1 el cual esta definido como constante en la variable ON para encender 
//los aspersores
void PrenderAspersores(){
    Aspersor1=ON;
    Aspersor2=ON;
}

//Manda un valor de 1 el cual esta definido como constante en la variable llamada ON para encender
//los Ventiladores

void PrenderVentiladores(){
    Ventilador1=ON;
    Ventilador2=ON;
}

//Manda un valor de 1 el cual esta definido como constante en la variable llamada ON para encender
//el Calefactor
void PrenderCalefactor(){
    Calefactor=ON;
}

// Manda un valor de 0 el cual esta definido como constante en la variable OFF
//para apagar todos los leds
void ApagarLeds(){
    Led_Amarillo=OFF;
    Led_Rojo=OFF;
    Led_Verde=OFF;
}

//Recibe como como parametro dos variables de tipo booleano el cual dependiendo el 
//valor que hayan obtenido en la funcion :Comparar_T_H_Adecuados de la libreria DTH11
//se procede a prender los leds dependiendo del valor que tengan, si los dos son false se
//prendera el led rojo, si uno es falso se prendera el led amarillo y en caso de los dos 
//estar en true se prendera el led verde

void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada){
    ApagarLeds();
    if(TemperaturaAdecuada==false && HumedadAdecuada==false){
        Led_Rojo=ON;
    }else if(TemperaturaAdecuada==false || HumedadAdecuada==false){
        Led_Amarillo=ON;
    }else{
        Led_Verde=ON;
    }
}

/*
 Recibe como parametros  un puntero de tipo char que tendra la humedad actual,
 * un entero que corresponde a la humedad digitada por el usuario y el margen
 * de error que digito el usuario para la humedad.
 *La humedad por encima del limite se controla con ventiladores.
 *La humedad por de bajo del limite se controla con aspersores. 
 */
void ControlHumedadAspersorVentilador(char *HumedadActual,int HumedadDigitada,int MargenErrorH){
    if(*HumedadActual<HumedadDigitada-MargenErrorH){
        PrenderAspersores();
    }else if(*HumedadActual>HumedadDigitada+MargenErrorH){
        if(VentiladoresEncendidosTemp!=true){
            PrenderVentiladores();
            VentiladoresEncendidosHum=true;
        }
    }else{
        ApagarAspersores();
        if(VentiladoresEncendidosTemp!=true){
            ApagarVentiladores();
            VentiladoresEncendidosHum=false;
        }
    }
}

/*
 Recibe como parametros  un puntero de tipo char que tendra la temperatura actual,
 * un entero que corresponde a la temperatura digitada por el usuario y el margen 
 * de error que digito el usuario.
 * la temperatura por debajo del rango se controla activando el calefactor.
 * la humedad por encima del rango se controla activando los ventiladores.
 * 
 */
void ControlTemperaturaCalefactorVentilador(char *TempActual,int TempDigitada,int MargenErrorT){
    if(*TempActual>TempDigitada+MargenErrorT){
        if(VentiladoresEncendidosHum!=true){
        PrenderVentiladores();
        VentiladoresEncendidosTemp=true;
        }
    }else if(*TempActual<TempDigitada-MargenErrorT){
        PrenderCalefactor();

    }else{
        ApagarCalefactor();
        if(VentiladoresEncendidosHum!=true){
          ApagarVentiladores();
          VentiladoresEncendidosTemp=false;  
        }
    }
}
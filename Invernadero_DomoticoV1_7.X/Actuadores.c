

#include "Actuadores.h"
#include "pinout.h"

#define ON 1
#define OFF 0



void initActuadores(){
    Confi_AspersoresVentiladores=0x00;
    Configuracion_Puertos_Leds  = 0;
}

void ApagarAspersores(){
    Aspersor1=OFF;
    Aspersor2=OFF;
}
void ApagarVentiladores(){
    Ventilador1=OFF;
    Ventilador2=OFF;
}

void PrenderAspersores(){
    Aspersor1=ON;
    Aspersor2=ON;
}

void PrenderVentiladores(){
    Ventilador1=ON;
    Ventilador2=ON;
}

void ApagarLeds(){
    Led_Amarillo=OFF;
    Led_Rojo=OFF;
    Led_Verde=OFF;
}
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

void ControlHumedadAspersor(char *HumedadActual,int HumedadDigitada,int MargenErrorH){
    if(*HumedadActual<HumedadDigitada-MargenErrorH){
        PrenderAspersores();
    }else{
        ApagarAspersores();
    }
}

void ControlTemperaturaVentilador(char *TempActual,int TempDigitada,int MargenErrorT){
    if(*TempActual>TempDigitada+MargenErrorT){
        PrenderVentiladores();
    }else{
        ApagarVentiladores();
    }
}
/* 
 * File:   Actuadores.h
 * Author: Servitech D&M
 *
 * Created on 10 de octubre de 2021, 08:43 PM
 */

#ifndef ACTUADORES_H
#define	ACTUADORES_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdio.h>
    
    
void initActuadores();    
void ApagarAspersores();
void ApagarVentiladores();
void PrenderAspersores();
void PrenderVentiladores();
void ApagarLeds();
void PrenderLed(bool TemperaturaAdecuada,bool HumedadAdecuada);
void ControlTemperaturaVentilador(char *TempActual,int TempDigitada,int MargenErrorT);
void ControlHumedadAspersor(char *HumedadActual,int HumedadDigitada,int MargenErrorH);

#ifdef	__cplusplus
}
#endif

#endif	/* ACTUADORES_H */


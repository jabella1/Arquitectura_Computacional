/* 
 * File:   DHT11.h
 * Author: Servitech D&M
 *
 * Created on 7 de octubre de 2021, 10:52 PM
 */
#include <stdio.h>
#include <stdbool.h>

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();


void DatosSensorTH(char Datos[]);
void Comparar_T_H_Adecuados(char *TempActual,char *HumActual,int TempDigitada,
        int HumDigitada,int MargenErrorT,int MargenErrorH);

#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */


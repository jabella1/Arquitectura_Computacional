/* 
 * File:   Variables.h
 * Author: Servitech D&M
 *
 * Created on 10 de octubre de 2021, 09:48 PM
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

   
#include <stdbool.h>

    unsigned char Temperatura[2];
    unsigned char Humedad[2];
    unsigned char MargenErrorT[1];
    unsigned char MargenErrorH[1];
    int MargenET=0;
    int MargenEH=0;
    char Datos[2];
    char Cadena[10];
    int TemperaturaAdecuada=0;
    int HumedadAdecuada=0;
    bool PrimeraVez=true;


#ifdef	__cplusplus
}
#endif

#endif	/* VARIABLES_H */


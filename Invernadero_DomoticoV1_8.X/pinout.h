/* 
 * File:   pinout.h
 * Author: Servitech D&M
 *
 * Created on 21 de septiembre de 2021, 11:28 AM
 */

#ifndef PINOUT_H
#define	PINOUT_H

#ifdef	__cplusplus
extern "C" {
#endif
 #include <pic18f4550.h>
 #include "Config.h"  
 #include <stdio.h>

//Configuracion ventiladores y aspersores
#define Confi_AspersoresVentiladoresCalefactor TRISC  

    // ASPERSORES

 #define Aspersor1  LATC0
#define  Aspersor2  LATC1 

//Ventiladores
#define Ventilador1 LATC2
#define Ventilador2 LATC6
 
//Calefactor

#define Calefactor LATC7
    
    
//Configuracion Sensor Temperatura y humedad DHT11
#define Data_Out LATA0              // assign Port pin for data/
#define Data_In PORTAbits.RA0       // read data from Port pin/
#define Data_Dir TRISAbits.RA0      // Port direction 
    



//Configuracion Puerto E para Leds.    
#define Configuracion_Puertos_Leds TRISE
#define Led_Rojo LATE0
#define Led_Amarillo LATE1
#define Led_Verde LATE2
    
    //CONFIGURACION PINS DEL LCD

#define RS LATD0                    /*PIN 0 of PORTB is assigned for register select Pin of LCD*/
#define EN LATD1                    /*PIN 1 of PORTB is assigned for enable Pin of LCD */
#define ldata LATD                  /*PORTB(PB4-PB7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD
    
 //CONFIGURACION PONS DEL TECLADO
    
#define write_port LATB  /* latch register to write data on port */
#define read_port PORTB  /* PORT register to read data of port */
#define Direction_Port TRISB
    
#define PTECLADO  TRISD
#define FILAS     LATD
#define COLUMNAS  PORTD    

#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */


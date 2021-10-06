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

//Configuracion Sensor Temperatura
#define Configuracion_Sensor_Temperatura TRISA0_bit


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

#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */


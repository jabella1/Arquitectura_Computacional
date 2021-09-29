/* 
 * File:   keypad.h
 * Author: ASUS
 *
 * Created on 25 de noviembre de 2020, 08:18 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H



#ifdef	__cplusplus
extern "C" {
#endif
#include "Config.h"
    
#define PB7     7 
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* FILAS-SALIDAS */
#define ROW1   PB0
#define ROW2   PB1
#define ROW3   PB2
#define ROW4   PB3
/* COLUMNAS-ENTRADAS */
#define COL1   PB4
#define COL2   PB5
#define COL3   PB6
#define COL4   PB7

#define PTECLADO  TRISD
#define FILAS     LATD
#define COLUMNAS  PORTD

#include "pinout.h"
   
    
void keypad_init (void);
char keypad_getkey(void);
unsigned char keyfind();  /* function to find pressed key */

short readKeypad();  //Scan the Keypad
char decodeCharacter(short a);  //Convert keypad value to character

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */


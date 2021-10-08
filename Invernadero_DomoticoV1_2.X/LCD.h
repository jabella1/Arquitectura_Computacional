/*!
\file   LCD.h
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  configuration LCD 16X2 4BITS.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2021. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

#include <pic18f4550.h>
#include "Config.h"
    

   
#define CMD_CLEAR_LCD 0x01
    
void LCD_Init();                    /*Initialize LCD*/
void LCD_Command(unsigned char );   /*Send command to LCD*/
void LCD_Char(unsigned char x);     /*Send data to LCD*/
void LCD_String(const char *);      /*Display data string on LCD*/
void LCD_String_xy(char, char , const char *);
void LCD_Clear();                   /*Clear LCD Screen*/


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */


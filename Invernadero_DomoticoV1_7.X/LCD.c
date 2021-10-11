/*!
\file   LCD.c
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
#include "LCD.h"
#include "pinout.h"
#include "keypad.h"


void LCD_Init()
{
    LCD_Port = 0;                   /*PORT as Output Port*/
    __delay_ms(15);                    /*15ms,16x2 LCD Power on delay*/
    LCD_Command(0x02);              /*send for initialization of LCD 
                                     *for nibble (4-bit) mode */
    LCD_Command(0x28);              /*use 2 line and 
                                     *initialize 5*8 matrix in (4-bit mode)*/
	LCD_Command(CMD_CLEAR_LCD);              /*clear display screen*/
    LCD_Command(0x0c);              /*display on cursor off*/
	LCD_Command(0x06);              /*increment cursor (shift cursor to right)*/	   
}

void LCD_Command(unsigned char cmd )
{
	ldata = (ldata & 0x0f) |(0xF0 & cmd);   /*Send higher nibble of command first to PORT*/ 
	RS = 0;                                 /*Command Register is selected i.e.RS=0*/ 
	EN = 1;                                 /*High-to-low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (ldata & 0x0f) | (cmd<<4);      /*Send lower nibble of command to PORT */
	EN = 1;
	NOP();
	EN = 0;
	__delay_ms(3);
}

void LCD_Char(unsigned char dat)
{
	ldata = (ldata & 0x0f) | (0xF0 & dat);   /*Send higher nibble of data first to PORT*/
	RS = 1;                                  /*Data Register is selected*/
	EN = 1;                                  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (ldata & 0x0f) | (dat<<4);               /*Send lower nibble of data to PORT*/
	EN = 1;                         /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	__delay_ms(3);
}
void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location = (0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location = (0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}

void LCD_Clear()
{
   	LCD_Command(CMD_CLEAR_LCD);     /*clear display screen*/
    __delay_ms(3);
    LCD_Command (0x80);                                //8 is for first line and 0 is for 0th position 
    __delay_ms(1);
}





void PedirDato(String Etiqueta,unsigned char vecLlenar[],int CantDatos){
     LCD_Clear();
     
     unsigned char tecla;
     LCD_String_xy(0,0,Etiqueta);
     LCD_Command(0xC0);  /* display pressed key on 2nd line of LCD */
     
     for(int i=0 ; i < CantDatos ; i++){
     do{    
     tecla=keyfind();
     }while(tecla=='*'||tecla=='#');
     LCD_Char(tecla);
     vecLlenar[i] = tecla;
   
     }
     __delay_ms(100);
     LCD_Clear();
}

void ConfigurarPuertosLCD(){
LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
}


void PedirTodosLosDatos(unsigned char Temperatura[],unsigned char Humedad[],unsigned char MargenErrorT[],unsigned char MargenErrorH[]){
       PedirDato("Temp. Adecuada",Temperatura,2);
       __delay_ms(100);
       PedirDato("Mgn Error Temp",MargenErrorT,1);
        __delay_ms(100);
       PedirDato("Hum. Adecuada",Humedad,2);
       __delay_ms(100);
       PedirDato("Mgn Error Hum",MargenErrorH,1);
}

void MostrarHumedad(char Cadena[],char Humedad){
        sprintf(Cadena,"%d",Humedad);
        LCD_String_xy(0,0,Cadena);
        sprintf(Cadena,".%d",0);
        LCD_Char('%');
        sprintf(Cadena,"  Hum.");
        LCD_String(Cadena);
}

 void  MostrarTemperatura(char Cadena[],char Temperatura){
       sprintf(Cadena,"%d",Temperatura);
       LCD_String_xy(2,0,Cadena);
       sprintf(Cadena,".%d",0);
       LCD_Char(0xdf);
       sprintf(Cadena,"C Temp.");
       LCD_String(Cadena);
 }

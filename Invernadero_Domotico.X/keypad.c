#include <xc.h>
#include "keypad.h"

void keypad_init(void){
   
    PTECLADO &= ~(1<<PB0) & ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3);   // FILAS    - SALIDA
    PTECLADO |= (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<<PB7);       // COLUMNAS - ENTRADA
    INTCON2bits.RBPU = 0;   //   PORTB pull-ups are enabled by individual port latch values 
}

char keypad_getkey(void){

char letras[4][4]={  {'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};
int  i=0;
char valor=0;

for(i=0;i<4;i++){

   if(i==0){

      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(1<<ROW2)|(0<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[0][0];}   //1
      while (!(COLUMNAS & (1<<COL2))){valor=letras[0][1];}   //2
      while (!(COLUMNAS & (1<<COL3))){valor=letras[0][2];}   //3
      while (!(COLUMNAS & (1<<COL4))){valor=letras[0][3];}   //A
   }

   if(i==1){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(0<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[1][0];}   //4
      while (!(COLUMNAS & (1<<COL2))){valor=letras[1][1];}   //5
      while (!(COLUMNAS & (1<<COL3))){valor=letras[1][2];}   //6
      while (!(COLUMNAS & (1<<COL4))){valor=letras[1][3];}   //B
   }

   if(i==2){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(0<<ROW3)|(1<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[2][0];}   //7
      while (!(COLUMNAS & (1<<COL2))){valor=letras[2][1];}   //8
      while (!(COLUMNAS & (1<<COL3))){valor=letras[2][2];}   //9
      while (!(COLUMNAS & (1<<COL4))){valor=letras[2][3];}  //C
   }

   if(i==3){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(0<<ROW4)|(1<<ROW3)|(1<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[3][0];}   //*
      while (!(COLUMNAS & (1<<COL2))){valor=letras[3][1];}   //0
      while (!(COLUMNAS & (1<<COL3))){valor=letras[3][2];}   //+
      while (!(COLUMNAS & (1<<COL4))){valor=letras[3][3];}   //D
      }
   }

   return valor;
}


short readKeypad()  //Scan the Keypad
{
    LATDbits.LATD3 = 1;
    __delay_us(10);
    if(PORTDbits.RD0 == 1)
    {
        while(PORTDbits.RD0 == 1);
        return 3;
    }
    else if(PORTDbits.RD1 == 1)
    {
        while(PORTDbits.RD1 == 1);
        return 2;
    }
    else if(PORTDbits.RD2 == 1)
    {
        while(PORTDbits.RD2 == 1);
        return 1;
    }
    
    LATDbits.LATD3 = 0;
    LATDbits.LATD4 = 1;
    __delay_us(10);
    
    if(PORTDbits.RD0 == 1)
    {
        while(PORTDbits.RD0 == 1);
        return 6;
    }
    else if(PORTDbits.RD1 == 1)
    {
        while(PORTDbits.RD1 == 1);
        return 5;
    }
    else if(PORTDbits.RD2 == 1)
    {
        while(PORTDbits.RD2 == 1);
        return 4;
    }
    
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 1;
    __delay_us(10);
    
    if(PORTDbits.RD0 == 1)
    {
        while(PORTDbits.RD0 == 1);
        return 9;
    }
    else if(PORTDbits.RD1 == 1)
    {
        while(PORTDbits.RD1 == 1);
        return 8;
    }
    else if(PORTDbits.RD2 == 1)
    {
        while(PORTDbits.RD2 == 1);
        return 7;
    } 
    
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;
    __delay_us(10);
    
    if(PORTDbits.RD0 == 1)
    {
        while(PORTDbits.RD0 == 1);
        return 12;
    }
    else if(PORTDbits.RD1 == 1)
    {
        while(PORTDbits.RD1 == 1);
        return 11;
    }
    else if(PORTDbits.RD2 == 1)
    {
        while(PORTDbits.RD2 == 1);
        return 10;
    }  
    LATDbits.LATD6 = 0;
    return 0;
}

char decodeCharacter(short a)  //Convert keypad value to character
{
    switch(a)
    {
        case 11 : return '0';
        case 1 : return '1';
        case 2 : return '2';
        case 3 : return '3';
        case 4 : return '4';
        case 5 : return '5';
        case 6 : return '6';
        case 7 : return '7';
        case 8 : return '8';
        case 9 : return '9';
    }
}




unsigned char col_loc,rowloc,temp_col;

unsigned char keypad[4][4]= {'1','2','3','/',
                             '4','5','6','*',
                             '7','8','9','-',
                             '*','0','#','+'};

unsigned char keyfind()
{      
    
    Direction_Port = 0xf0;  /* PORTD.0-PORTD.3 as a Output Port and PORTD.4-PORTD.7 as a Input Port*/
    unsigned char temp1;
   
        write_port = 0xf0;  /* Make lower nibble as low(Gnd) and Higher nibble as High(Vcc) */
      do
      {
        do
        {
          
            col_loc = read_port & 0xf0;  /* mask port with f0 and copy it to col_loc variable */   
        
        }while(col_loc!=0xf0);  /* Check initially at the start there is any key pressed*/ 
         col_loc = read_port & 0xf0;  /* mask port with f0 and copy it to col_loc variable */  
      }while(col_loc!=0xf0);
      
      __delay_ms(30);
        write_port = 0xf0;  /* Make lower nibble as low(Gnd) and Higher nibble as High(Vcc) */
        do
        { do
            
            {
               
                col_loc = read_port & 0xf0;
            }while(col_loc==0xf0);  /* Wait for key press */
         col_loc = read_port & 0xf0;
        }while(col_loc==0xf0);  /* Wait for key press */
               
        __delay_ms(30);
         
        col_loc = read_port & 0xf0;
               
   
    
    while(1)
    {
        write_port  = 0xfe;  /* make Row0(D0) Gnd and keep other row(D1-D3) high */
        col_loc = read_port & 0xf0;         /* Read Status of PORT for finding Row */
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=0;  /* If condition satisfied get Row no. of key pressed */
            while(temp_col!=0xf0)  /* Monitor the status of Port and Wait for key to release */
            {
                temp_col = read_port & 0xf0;  /* Read Status of PORT for checking key release or not */    
            }
            break;
        }
        
        write_port = 0xfd;  /* make Row1(D1) Gnd and keep other row(D0-D2-D3) high */
        col_loc = read_port & 0xf0;  /* Read Status of PORT for finding Row */
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=1;  /* If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)  /* Monitor the status of Port and Wait for key to release */
            {
                temp_col = read_port & 0xf0;  /* Read Status of PORT for checking key release or not */
            }
            break;
        }
        
        write_port = 0xfb;  /* make Row0(D2) Gnd and keep other row(D0-D1-D3) high */
        col_loc = read_port & 0xf0;  /* Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=2;  /* If condition satisfied get Row no. of key pressed */
            while(temp_col!=0xf0)  /* Wait for key to release */
            {
                temp_col = read_port & 0xf0;  /* Read Status of PORT for checking key release or not */
            }
            break;
        }
        
        write_port = 0xf7;  /* make Row0(D3) Gnd and keep other row(D0-D2) high */
        col_loc = read_port & 0xf0;  /* Read Status of PORT for finding Row */
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=3;  /* If condition satisfied get Row no. of key pressed */
            while(temp_col!=0xf0)  /* Wait for key to release */
            {
                temp_col = read_port & 0xf0;  /* Read Status of PORT for checking key release or not */
            }
            break;
        }
        
    }

    
    while(1)
    {
        
        if(col_loc==0xe0)
        {
             return keypad[rowloc][0];  /* Return key pressed value to calling function */            
        }
        else 
            if(col_loc==0xd0)
        {
            return keypad[rowloc][1];  /* Return key pressed value to calling function */   
        }
        else
            if(col_loc==0xb0)
        {
            return keypad[rowloc][2];  /* Return key pressed value to calling function */
        }
        else
            
        {
            return keypad[rowloc][3];  /* Return key pressed value to calling function */           
        }    
    }
    
   __delay_ms(30);     
 
}
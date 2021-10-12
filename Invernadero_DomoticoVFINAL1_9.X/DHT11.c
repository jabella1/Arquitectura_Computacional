
#include "pinout.h"
#include "DHT11.h"
#include "Actuadores.h"
#include <xc.h> 




// Espere pulso de 0, este es el inicio del pulso de datos y después comprueba si los 
//datos recibidos es un 1 o un 0.. para al final retornar una variable tipo char con el 
//valor de la temperatura o humedad detectada por el sensor.

char DHT11_ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(Data_In & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(Data_In & 1);
    }
  return data;
}

//configura como salida los pines donde esta conectado el sensor y lo inicializa
void DHT11_Start()
{    
    
    Data_Dir = 0;       /* set as output port */
    Data_Out = 0;       /* send low pulse of min. 18 ms width */
    __delay_ms(18);
    Data_Out = 1;       /* pull data bus high */
    __delay_us(20);
    Data_Dir = 1;       /* set as input port */    
//    LED = 14;
}



void DHT11_CheckResponse()
{
    while(Data_In & 1);     /* wait till bus is High */     
    while(!(Data_In & 1));  /* wait till bus is Low */
    while(Data_In & 1);     /* wait till bus is High */
}


//Recibe como parametro un vector de tipo char el cual se llenara internamente con la
//funcion DHT11_ReadData() , en la posicion 0 del vector se guarda 
//la Temperatura y en la posicion 1 del vector se guarda la Humedad arrojada por el sensor.

void DatosSensorTH(char Datos[]){
         char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
         char Checksum;
         DHT11_Start();                  // send start pulse to DHT11 module */
         DHT11_CheckResponse();          // wait for response from DHT11 module */
    
         //read 40-bit data from DHT11 module 
         RH_Integral = DHT11_ReadData(); //lee la humedad actual por medio del
                                         //sensor y la guarda en RH_Integral
         RH_Decimal = DHT11_ReadData();  // read Relative Humidity's decimal value 
         
         T_Integral = DHT11_ReadData();  //lee la Temperatura actual por medio del
                                         //sensor y la guarda en T_Integral
         T_Decimal = DHT11_ReadData();   // read Relative Temperature's decimal value 
         Checksum = DHT11_ReadData();    // read 8-bit checksum value
         
         
         Datos[0]=T_Integral;            
         Datos[1]=RH_Integral;
}

//Recibe como parametros dos punteros de tipo char que hacen referencia a la
//temperatura y humedad actual que se obtuvieron en el vector que se lleno en
//la función DatosSensorTH(char Datos[]); tambien recibe la TempDigitada,HumDigitada y los margenes
//de error de la temperatura y humedad todos estos digitados por el usuario, y hace un 
//calculo interno para comprobar que la temperatura actual este dentro del rango requerido?
//dependiendo de los calculos realizados mandara los datos obtenidos a la funcion PrenderLeds
//para prender los leds que correspondan a los calculos obtenidos.


void Comparar_T_H_Adecuados(char *TempActual,char *HumActual,int TempDigitada,
        int HumDigitada,int MargenErrorT,int MargenErrorH){
    bool TemperaturaAdecuada= true;
    bool HumedadAdecuada =true;
    if(*TempActual<TempDigitada-MargenErrorT || *TempActual >TempDigitada+MargenErrorT){
           TemperaturaAdecuada=false; 
    }
    if(*HumActual<HumDigitada-MargenErrorH || *HumActual>HumDigitada+MargenErrorH){
        HumedadAdecuada=false;
    }
   PrenderLed(TemperaturaAdecuada,HumedadAdecuada);
}


// configura los bits analogicos/digitales como digitales.
void initDHT11(){
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */  
}
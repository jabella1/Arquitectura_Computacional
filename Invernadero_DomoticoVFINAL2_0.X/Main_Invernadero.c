#include <xc.h>
#include "Config.h"
#include "pinout.h"
#include "LCD.h"
#include "keypad.h"
#include "DHT11.h"
#include "Actuadores.h"
#include "Variables.h"

void main(){
    OSCCON=0x72;        //se configura el oscilador interno con frecuencia de 8 MHz.
    initDHT11();        //ADCON1=0x0F configura los bits analogicos/digitales como digitales.
    initActuadores();   //Configura como salida los puertos donde estan conectados los actuadores.
    LCD_Init();         //Configura como salida los puertos donde esta conectado el LCD
                        //y lo Inicializa.
    initTeclado();      //RBPU=0  conecta el puerto b a 5vcc a traves de una resistencia interna
                        //de esta manera se puede usar el teclado matriarcal.
    ApagarActuadores(); //Se apagan los actuadores.
    while(1){   
     if(PrimeraVez==true){  
         PedirTodosLosDatos(Temperatura,Humedad,MargenErrorT,MargenErrorH); //Llena internamente los
                                                                            //parametros que se le pasan
         TemperaturaAdecuada = DatoDigitadoAEntero(Temperatura); // Convierte la temperatura que se digito
                                                                 // a un entero
         HumedadAdecuada = DatoDigitadoAEntero(Humedad);// Convierte la humedad que se digito
                                                        // a un entero
         MargenET = MargenErrorT[0]-48; // convierte el margen de error de temperatura a entero.
         MargenEH = MargenErrorH[0]-48; // convierte el margen de error de la humedad  a entero.
         PrimeraVez=false;
    }
        DatosSensorTH(Datos); // se llena el vector de dos posiciones que se paso por parametros.
                              //Datos[0] contiene la temperatura actual.
                              //Datos[1] contiene la humedad actual.
        Comparar_T_H_Adecuados(&Datos[0],&Datos[1],TemperaturaAdecuada,
                HumedadAdecuada,MargenET,MargenEH); // calcula internamente que la temperatura actual y
                                                    // la humedad actual esten dentro del rango optimo.
                                            //[TemperaturaAdecuada-MargenET,TemperaturaAdeciada+MargenET]
                                            //[HumedadAdecuada-MargenEH,HumedaAdecuada+MargenEH].
                                            //dependiendo de los calculos prendera el led que corresponda
        ControlHumedadAspersorVentilador(&Datos[1],HumedadAdecuada,MargenEH); // se encarga de prender los aspersores
                                                 //en caso de que la humedad actual este por debajo de los
                                                 // limites.
        ControlTemperaturaCalefactorVentilador(&Datos[0],TemperaturaAdecuada,MargenET); // se encarga de
                                             //prender o apagar los aspersores y ventiladores.
                                             //si la temperatura actual esta por debajo de los limites
                                             //se prende el calefactor.
                                             //si la temperatura actual esta por encima de los limites
                                             //se prenden los ventiladores..
                                             // si la temperatura actual esta dentro de los limites
                                             // se apagan los ventiladores y el calefactor
        
        MostrarHumedad(Cadena,Datos[1]); // muestra en el LCD la humedad.
    
        MostrarTemperatura(Cadena,Datos[0]); // muestra en el LCD la temperatura.
       
       __delay_ms(500);  // retraso de 0.5 segundos.
     }
}





/* 
 * File:   DHT11.h
 * Author: Servitech D&M
 *
 * Created on 7 de octubre de 2021, 10:52 PM
 */

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();


#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */


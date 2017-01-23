/****************************************************************************
* Fichier: TP7_P2.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 23 octobre 2016
* Description:
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"
/*
#define DIXCM 11111111
#define VINGCM 10001001
#define TRENTECM 01100010
#define QUARANTECM 01001001
#define CINQUANTECM 00111011
//#define 60CM 00110001
//#define 70CM 00101100
//#define 80CM 00100111
#define OUT_RANGE 00000000
*/

void initialisationUART ( void ) {
UBRR0H = 0;
UBRR0L = 0xCF;
UCSR0A = 0x00;  
UCSR0B = 0x18; 
UCSR0C = 0x06;
} 
void transmissionUART ( uint8_t nombre8Bit ) {		
while (!(UCSR0A & (1 << UDRE0))){}
UDR0 = nombre8Bit;
}


int main()
{
	DDRB = 0xff;
	DDRA = 0x00; //mettre bonne pin

	uint16_t nombre16Bit;
	initialisationUART();
	can cann;
	int somme=0;
	nombre16Bit =cann.lecture(7);
	nombre16Bit = nombre16Bit >> 2;				
	uint8_t valeur1= (nombre16Bit & 0x00ff);
	//uint8_t valeur1= 0;
	uint8_t valeur2;
	bool sensCroissant = false;
	uint8_t nombreCoins=0;
	for (int i=0; i<40; i++){
		for (int j=0; j<5; j++){
			_delay_ms(20);
			nombre16Bit =cann.lecture(7);
			nombre16Bit = nombre16Bit >> 2;				
			somme +=(nombre16Bit & 0x00ff);
			transmissionUART(somme);
			}
			valeur2 = somme/5;
			somme =0;
			if (sensCroissant){
				if(valeur1 >(valeur2+5)){
					nombreCoins ++;
					sensCroissant= false;
					}
				
				}
			else {
				if((valeur1+5 ) < valeur2){
					nombreCoins ++;
					sensCroissant= true;
					}
				}	
			valeur1=valeur2;	
			transmissionUART(nombreCoins);
	}
	transmissionUART(nombreCoins);
	_delay_ms(20);

	if (nombreCoins <2)
		PORTB=0x01;
	else if (nombreCoins <4)
		PORTB=0x02;
	else{
		for(;;){
		PORTB=0x01;
		_delay_ms(100);
		PORTB=0x00;
		_delay_ms(100);
		
	}
		}	
		
}




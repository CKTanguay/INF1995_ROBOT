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
#include "Del.h"
#include "FonctionDelai.h"
#include "pwm_moteur.cpp"

#define DIXCM 11111111
#define VINGTCM 10001001
#define TRENTECM 01100010
#define QUARANTECM 01001001
#define CINQUANTECM 00111011
#define SOIXANTECM 00110001
#define SOIXANTEDIXCM 00101100
#define QUATREVINGTCM 00100111
#define OUT_RANGE 00000000

//valeur max = 182~185 -->environ 7cm

void initialisationUART ( void ) 
{
	UBRR0H = 0;
	UBRR0L = 0xCF;
	UCSR0A = 0x00;  
	UCSR0B = 0x18; 
	UCSR0C = 0x06;
} 

void transmissionUART ( uint8_t nombre8Bit ) 
{		
	while (!(UCSR0A & (1 << UDRE0))){}
	UDR0 = nombre8Bit;
}


int main()
{
	DDRB = 0xff;
	DDRA = 0x00; //mettre bonne pin
	DDRC = 0x00;

	initialisationUART();
	can cann;
	
	Del del;
						
	while(true)
	{
		uint16_t nombre16Bit = cann.lecture(7);
		nombre16Bit = nombre16Bit >> 2;
		uint8_t nombre8Bit;
		nombre16Bit &= 0x00ff;
		nombre8Bit= nombre16Bit;
		transmissionUART(nombre8Bit);
		_delay_ms(300);
		
		
	}
}



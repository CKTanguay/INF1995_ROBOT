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

int main()
{
	DDRB = 0xff;
	DDRA = 0x00;

	uint16_t nombre16Bit;
	uint8_t vert =80;		//Valeur maximale correspondant à l'éclairage de niveau faible.
	uint8_t rouge =252;		//Valeur maximale correspondant à l'éclairage de bon niveau.
	
	for (;;)
	{
		can cann;							//Initialisation de l'objection convertisseur.
		nombre16Bit =cann.lecture(0);		//Appel de la fonction de lecture de l'objet cann avec la position 0 sur le port A.
		nombre16Bit >> 2;					//Décalage du résultat de deux bits vers la droite.
		uint8_t nombre8Bit = nombre16Bit;	

		if (nombre8Bit > vert && nombre8Bit < rouge)			//Vérification des conditions pour déterminer si la couleur sera ambrée.
		{
				PORTB=0x01;
				_delay_ms(1);
				PORTB=0x02;
				_delay_ms(4);
		}

		else if(nombre8Bit >= 0 && nombre8Bit <= vert)		//Vérification des conditions pour déterminer si la couleur sera verte.
		{
			PORTB =0x02;	
		}

		else if(nombre8Bit >= rouge && nombre8Bit < 256)		//Vérification des conditions pour déterminer si la couleur sera rouge.
		{
			PORTB=0x01;	
		}
	}
}

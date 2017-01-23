/****************************************************************************
* Fichier: TP7_P1.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 23 octobre 2016
* Description:
*
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile bool condition;
volatile uint8_t compteur=0;

ISR(TIMER1_COMPA_vect)
{
  compteur++;	//Incrémentation du compteur dans la routine ISR.
}

void initialisation(void) //Initialisation des ports en entrée et sortie et la LED est éteinte.
{
	cli ();
	DDRB = 0xff;
  	DDRD = 0x00;
	sei ();
	PORTB=0x00;
}

void partirTimer(int duree) 
{
		TCNT1 = 0;		//Initialisation du compteur TCNT1 à 0.
		OCR1A = duree;	//Initialisation de la valeur de comparaison à la duréee passée en paramètre.
		TCCR1A = 0x00;
		TCCR1B = _BV(WGM12)|_BV(CS12)|_BV(CS10); //Initialisation du mode et du prescaler.
		TCCR1C = 0;
		TIMSK1 = _BV(OCIE1A); //Initialisation du masque.
}

bool boutonAppuyer()	//Vérification de l'état du bouton.
{
	if (!(PIND & 0x04)) 
	{
		_delay_ms(10);
		return (!(PIND & 0x04));
	}
	return false;
}

int main()
{
	initialisation();
	int vitesseCompteur =781; 	//Valeur d'un dixième de seconde avec un prescaler de 1024.

	for(;;)
  	{
		compteur=0;
		if (boutonAppuyer())	//Si le bouton est enfoncé.
    	{
			partirTimer(vitesseCompteur);	//Appel du compteur.
			do{} while (compteur <= 120 && boutonAppuyer());	//On ne fait rien tant que le bouton est enfoncé ou que le compteur
																//n'atteint pas la valeur maximale 120.
			TIMSK1 = 0;
			PORTB=0x02;			//
			_delay_ms(500);		//La DEL prend la couleur verte pour une demi-seconde.
			PORTB=0x00;			//
			_delay_ms(2000);	//On éteint la DEL et on attend deux secondes.

			for (int i=0; i < (compteur); i++) //La DEL devient rouge et on la fait clignoter un nombre de fois égal à la valeur du compteur divisé par deux.
			{									 
				PORTB^=0x01;	//On fait un OU binaire pour comparer la valeur du PORT et lui assigner la valeur en conséquence.
				_delay_ms(250);
			}

			PORTB=0x02;			
			_delay_ms(1000);	//La DEL prend la couleur verte pour une seconde.
			PORTB=0x00;			//On éteint la DEL.
		}

	}
	return 0;
}

/****************************************************************************
* Fichier: TP7_P1.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 18 octobre 2016
* Description: 
*
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile bool condition =true;
volatile uint8_t nbDemiSecondes =0;
   ISR (TIMER1_COMPA_vect) {
	condition = false;
	nbDemiSecondes++;
	TCNT1 = 0;
	
}
void initialisation ( void ) {

	cli ();
	DDRB = 0xff;   
    DDRC = 0x00;      
	sei ();
	PORTB=0x00;
	 

}
void reset(int duree){
			cli();
			TCNT1 = 0; 
			OCR1A = duree; 
			TCCR1A = 0x04; 
			TCCR1B = 0x05; 
			TCCR1C = 0; 
			TIMSK1 = _BV(OCIE1A);
			nbDemiSecondes=1;
			sei();
	}
int main()
{
	initialisation();
	for(;;){
		if(PINC&0x04)
			PORTB=0x00;
	else {
		//PORTB=0X00;
		int compteur=0;
		while (compteur <= 120 && !(PINC & 0x04)){ //test pas le rebond
			compteur ++;
			_delay_ms(100);
			}
			int uneDemiSec=3906;
			reset(uneDemiSec); 
			while (condition){
			PORTB=0x02;
			_delay_ms(50);
			PORTB=0x00;
			_delay_ms(50);	
		}
		_delay_ms(2000);
		reset(uneDemiSec);
		while (nbDemiSecondes<(compteur)){
		PORTB=0x01;
		_delay_ms(250);
		PORTB=0x00;
		_delay_ms(250);
	}
	PORTB=0x02;
	_delay_ms(1000);
	PORTB=0x02;
		}

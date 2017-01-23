/****************************************************************************
 * Fichier: TP3_P2.cpp
 * Auteurs: Maxime Brousseau 1828528
 *          Christophe Kedzierski-Tanguay 1827066
 * Date de dernière modification: 20 Septembre 2016
 * Ce programme fait alterner les couleurs de la led selon un certain ordre. 
 * 
 * État courant     #         Entrée bouton-poussoir       # Couleur de sortie (de l'état courant)
 *                  #        0          #        1         #        
 * etatInitial      #  etatInitial      # ambre            # Couleur rouge
 * ambre            #  vertInactif      # ambre            # Couleur ambre
 * vertInactif      #  vertInactif      # rougeActif       # Couleur verte
 * rougeActif       #  ledEteinte       # rougeActif       # Couleur rouge
 * ledEteinte       #  ledEteinte       # vertActif        # Aucune couleur
 * vertActif        #  etatInitial      # vertActif        # Couleur verte
 ****************************************************************************/
#ifndef F_CPU
/* fournir un avertissement mais non une erreur */
# warning "F_CPU pas defini pour 'memoire_24.cpp'"
# define F_CPU 8000000UL
#endif
#include "test.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include <pwm.h>
#include <controlDel.h>
#include <avr/interrupt.h>
volatile bool boutonAppuyer=true;
ISR (INT0_vect) { 
	boutonAppuyer=false;
	EIFR |= (1 << INTF0); 
   
}
void initialisation ( void ) {
	cli ();	
	DDRB = 0xff;   
    DDRD = 0x00;      
	EIMSK |= _BV(INT0);
	EICRA |= _BV(ISC00);
	sei ();

}

int main(){
	
	initialisation();
	Del del;
    del.allumerR();
	_delay_ms(1000);
	  del.allumerV();
	_delay_ms(1000);
	do{
	 //del.allumerA();
	 del.allumerR();
	 _delay_ms(1);
	 del.allumerV();
	 _delay_ms(4); 
	}while(boutonAppuyer);
	for(;;){
		pwm60Hz (25);
		
		}
	PORTB = 0x00;
    return 0;
}
    

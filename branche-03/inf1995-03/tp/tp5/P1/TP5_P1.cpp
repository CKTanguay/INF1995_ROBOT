/****************************************************************************
* Fichier: TP5_P1.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 20 Septembre 2016
* Description: 
*
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>

   
volatile uint8_t currentState =0; 
enum State {etatInitial, ambre, vertInactif, rougeActif, ledEteinte, vertActif, n_etat};
// placer le bon type de signal d'interruption
// a prendre en charge en argument
volatile State state;
volatile bool etatBouton;
    
ISR (INT0_vect) { // type interrup

	// laisser un delai avant de confirmer la reponse du
	// bouton-poussoir: environ 30 ms (anti-rebond)

	_delay_ms ( 30 );

	// Se souvenir ici si le bouton est presse ou relache
	
	//etatBouton =!etatBouton

	// changements d'etats tels que ceux de la

	// semaine precedente
	state = State((uint8_t(state)+1)% n_etat);

	// Voir la note plus bas pour comprendre cette instruction et son role

	EIFR |= (1 << INTF0); //il soccupe des reset de linterrup pr pouvoir en avoir dautres
   
}


void initialisation ( void ) {

	// cli est une routine qui bloque toutes les interruptions.
	
	// Il serait bien mauvais d'etre interrompu alors que
	
	// le microcontroleur n'est pas pret...
	
	cli ();
	
	
	// configurer et choisir les ports pour les entrees
	
	// et les sorties. DDRx... Initialisez bien vos variables
	
	DDRB = 0xff;   
    DDRD = 0x00;      
	
	
	// cette procédure ajuste le registre EIMSK
	
	// de ATmega324PA pour permettre les interruptions externes
	
	EIMSK |= _BV(INT0);
	
	
	// il faut sensibiliser les interruptions externes aux
	
	// changements de niveau du bouton-poussoir
	
	// en ajustant le registre EICRA
	
	EICRA |= _BV(ISC00);
	
	
	// sei permet de recevoir a nouveau des interruptions.
	
	sei ();

}


int main(){
	
	initialisation();
	
    int compteur=0;
	for(;;) {
    compteur++;
	switch(state)
        {
        
            case etatInitial:
            {
                PORTB=0x01;
                break;
            }
            
            case ambre:
            {
                    if (compteur %6 == 0)
                        PORTB = 0x01;
                    else PORTB = 0x02;
                break;                
            }
            
            case vertInactif:
            {
                PORTB=0x02;
                break;
            }
            
            case rougeActif:
            {
                PORTB=0x01;            
                break;
            }
            
            case ledEteinte:
            {
                PORTB=0x00;
             
               
                break;
            }
            
            case vertActif:
            {
           
                PORTB=0x02;
           
                break;
                
            }
            default:
				PORTB=0x02;
        }
	
}
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

/* 
 * Tableau des etats:
 * Etat Entrée	Etat Suivant	Sortie
 * 								R	Am	V
 * 
 * Init 0		Init			1	0	0
 * Init 1		E1				1	0	0
 * E1	0		E2				0	1	0
 * E1	1		E1				0	1	0
 * E2	0		E2				0	0	1
 * E2	1		E3				0	0	1
 * E3	0		E4				1	0	0	
 * E3	1		E3				1	0	0
 * E4	0		E4				0	0	0
 * E4	1		E5				0	0	0
 * E5	0		Init			0	0	1
 * E5	1		E5				0	0	1
 */
#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
using namespace std;

enum Etat {Init, E1, E2, E3, E4, E5};

volatile bool boutonPresse = false;
volatile Etat etat = Init;

void ambre(){
	PORTB = 0x01; 
    _delay_ms(6);
    PORTB = 0x02;
    _delay_ms(4);
}

// placer le bon type de signal d'interruption
// a prendre en charge en argument
ISR (INT0_vect) { // les renseignements sur les trois registres modifié ce trouvent
                  // pages 67 et 68 de la doc Atmel 
// laisser un delai avant de confirmer la reponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms ( 30 );
// Se souvenir ici si le bouton est presse ou relache
if ( PIND & 0x04 ){ //bouton pressé
        boutonPresse = true;
    }
	else
    {
        boutonPresse = false;
    }
// changements d'etats tels que ceux de la
// semaine precedente

 switch (etat){
        case Init :
            if ( boutonPresse ){ 
                etat = E1;
            }
            break;
        case ETAT1 :
            if (!boutonPresse){ 
                etat = E2;
            }
            break;
        case ETAT2 :
            if (boutonPresse){ 
                etat = E3;
            }
            break;
        case ETAT3 :
            if (!boutonPresse){ 
                etat = E4;
            }
            break;
        case ETAT4 :
            if (boutonPresse){ 
                etat = E5;
            }
            break;
        case ETAT5 :
            if (!boutonPresse){ 
                etat = Init;
            }
            break;
    }
// Voir la note plus bas pour comprendre cette instruction et son role
EIFR |= (1 << INTF0) ;
}


void initialisation ( void ) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'etre interrompu alors que
// le microcontroleur n'est pas pret...
cli ();

// configurer et choisir les ports pour les entrees
// et les sorties. DDRx... Initialisez bien vos variables
	DDRA = 0xff; // mode sortie
  	DDRB = 0xff; // mode sortie
  	DDRC = 0xff; // mode sortie
  	DDRD = 0x00; // mode entrée
  	PORTB = 0x00;
  

// cette procédure ajuste le registre EIMSK
// de ATmega324PA pour permettre les interruptions externes
EIMSK |= _BV(INT0); 

// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= 0x01 ; // Écrit 1 dans le bit de poid le plus faible dans EICRA  EICRA = 1 << ISC0

// sei permet de recevoir a nouveau des interruptions.
sei ();
}

int main()
{
    initialisation();
    for(;;){
        switch (etat){
            case Init: 
		    PORTB = 0x02; //Rouge
		    break;
		
		    case E1:
		    ambre();
		    break;
		
		    case E2: 
		    PORTB = 0x01; //Vert
		    break;
		
		    case E3: 
            PORTB = 0x02; //Rouge
            break;
            
            case E4: 
            PORTB = 0x00; //Eteinte
            break;
            
            case E5:
            PORTB = 0x01; //Vert
            break;	
        }
    }
}





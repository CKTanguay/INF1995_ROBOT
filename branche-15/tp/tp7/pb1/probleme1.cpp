/*
 * Fichier : probleme1.cpp
 * Auteur : Tom Avedissian
 * Date de création : 20 octobre 2016
 */
 

#define F_CPU 8000000  
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
	
volatile uint8_t compteur=0;  	// variable compteur
volatile bool bouton = false;  		// variable boolenne bouton
enum Etat {Init,E1,E2,E3,E4};	// différents etats possibles
Etat etat=Init; 				// etat initial

void delV()	// Del verte durant 1 sec
{
	PORTB=0x01;	// Del verte
	_delay_ms(1000);
	PORTB=0x00; // Del eteinte
}
	


void clignoteV()	// Del verte clignotante pendant 1/2 sec
{
	for(uint8_t i=0; i<10;++i) 
	{
	PORTB=0x01;
	_delay_ms(25);  
	PORTB=0x00;
	_delay_ms(25);             
	}
}


void clignoteR()	// DEl rouge clignotante compteur/2 fois
{
for(uint8_t i=0; i<(compteur/2);++i)	// compteur/2 fois 
	{
	PORTB=0x02;
	_delay_ms(250); // un clignotement toutes les 1/2 sec
	PORTB=0x00;
	_delay_ms(250);    
	}
}

ISR (TIMER1_COMPA_vect) // Fonction d'interruption incrémentant le compteur chaque 1/10 de sec
{	
	compteur++;         
	
}


ISR (INT0_vect)  // Fonction d'interruption par bouton poussoir
{
	_delay_ms(50);	// Anti-rebond 
	
	if(!(PIND & 0x04))	// si le bouton poussoir est pesé 
	{
	bouton = true;

	}
	if(PIND & 0x04)	// si le bouton poussoir n'est pas pesé 
	{
	bouton = false;
	}
	EIFR |= (1 << INTF0);
}

void partirMinuterie ( uint16_t duree ) {
    
    compteur = 0;	// Remise à zéro du compteur
    
    TCNT1 = 0; // La minuterie part de zéro
    
    OCR1A = duree; // Valeur de remise à zéro du timer
    
    TCCR1A = 0;
    
    TCCR1B = _BV(WGM12) | _BV(CS10) | _BV(CS12); // Mode CTC et prescaler 1024 
    
    TCCR1C = 0;
        
    TIMSK1 = _BV(OCIE1A); // TIMER1_COMPA_vect
    
}
void Initialisation ( void ) {
    
    // cli est une routine qui bloque toutes les interruptions.
    
    cli ();
        
    DDRB = 0xff; // PORT B est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree (bouton poussoir)
    
    // cette procédure ajuste le registre EIMSK
    
    // de ATmega324PA pour permettre les interruptions externes
    
    EIMSK |= _BV(INT0);
    
    // il faut sensibiliser les interruptions externes aux
    
    // changements de niveau du bouton-poussoir
    
    // en ajustant le registre EICRA
    
    EICRA |= 0x01;
    
    // sei permet de recevoir a nouveau des interruptions.
    
    sei ();
    
}


int main()               
{
Initialisation();	// Initialisation des interruptions externes
for(;;)           
{
switch (etat)                 
{
case Init:	                  
			
			if(bouton==true)	// si bouton pesé 
			{ 
			partirMinuterie(781);	// On lance la minuterie pour incrementer le compteur 10 fois par sec
			etat=E1;	// changement d'état
			}
			break;
			
			
case E1:	
			if( bouton == false || compteur >= 120)
			{	// si bouton non-pesé et compteur supérieur à 120
			TIMSK1 = 0;		// On arrête l'incrémentation du compteur en mettant le masque à zéro
			etat=E2;	// changement d'état		      
			}
			break;
			
			
case E2:
			clignoteV();     // Appel de la fonction clignoteV 
			_delay_ms(2000); // Del eteinte pendant 2 secondes
			etat=E3;      // Passe a l etat 3
			break;
			
			
case E3:
			
			clignoteR();     // Appel de la fonction clignoteR
			etat=E4;      // Passe a l'etat 4
			break;
			
case E4:
			
			delV();      // Appel de la fonction lumiereV
			etat=Init;       // Passe a l'etat initial
			break;
		
}			
}		
return 0;
}


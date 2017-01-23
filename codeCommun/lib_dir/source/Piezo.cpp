#include "Piezo.h"

void Piezo::initialisation(void) {
	
	
	DDRD |= (1 << DDD6) | (1 << DDD7); // On s'assure que les pins 4 et 5 du port D sont en mode sortie
	DDRD |= 0x04;
	
	TCCR2A |= (1 << COM2A0) | (1 << WGM21); // Toggle à la comparaison
	

	TCCR2B = (1 << CS22) |(1 << CS21) |(1 << CS20); // prescaler 1024 et mode CTC
	OCR2A = 0;
}



void Piezo::jouerSonAigu() 
{
	
	TCCR2B = (1 << CS22) |(1 << CS21) |(1 << CS20); // On remet le prescaler à 1024
	OCR2A = 18; // valeur nécessaire pour obtenir la note midi 81
}
	
	
	
void Piezo::arreterSon(void) 
{
	TCCR2B &= ~((1 << CS22) |(1 << CS21) |(1 << CS20)); // remet le prescaler à 0 (arrête le compteur)
	//TCCR1B &=0;
}





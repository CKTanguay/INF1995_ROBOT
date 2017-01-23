
#include "Piezo.h"


uint16_t Piezo::midiTable[37] = {4545,4290,4050,3822,3608,3405,3214,3034,2863,2703,2551,2407,2272,2145,2025,1911,1804,
1703,1607,1517,1432,1351,1276,1204,1136,1073,1012,956,901,851,803,758,716,675,638,602,568}; // on divise la fréquence du processeur 
																							// par la fréquence de la note fois 2
void Piezo::initialisation(void) {
	
	
	DDRD |= (1 << DDD4) | (1 << DDD5); // On s'assure que les pins 4 et 5 du port D sont en mode sortie
	
	TCCR1A |= (1 << COM1A0) | (1 << WGM11) | (1 << WGM10); // Toggle à la comparaison
	

	TCCR1B = (1 << CS11) | (1 << WGM13); // prescaller 8 et mode CTC
	TCCR1C = 0;
	OCR1A = 0;
}



void Piezo::jouerSon(uint8_t midi) 
{
	
	if (midi >= 45 && midi <= 81) {
		TCCR1B |= (1 << CS11); // On remet le prescaller à 8
		OCR1A = midiTable[midi-45]; 
	}
	else {
		TCCR1B &= ~(1 << CS10); // remet le prescaller à 0 (arrête le compteur)
	}
}
	
	
	
void Piezo::arreterSon(void) 
{
	TCCR1B &= (0 << CS11); // remet le prescaller à 0 (arrête le compteur)
	//TCCR1B &=0;
}





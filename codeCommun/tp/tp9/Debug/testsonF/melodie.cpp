//#include "Son.h"
//#include "Son.cpp" //A inclure, car on a pas de .h qui inclut le son.h uniquement

#include "Piezo.h"


int main()
 {
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	
	Piezo piezo;
	
	Piezo::initialisation();
	
		
	Piezo::jouerSon(55);


	
	
	Piezo::arreterSon();
				
	return 0;
}

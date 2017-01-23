
#include <avr/io.h>
#include <stdint.h>
#include "couleurs.h"

int main() {
	//initialisationUART();
	DDRC=0xff;
	DDRB=0xff;
	DDRD=0x01;
	partirScalerVingt();
	uint16_t red;
	uint16_t bleu;
	uint16_t vert;
	uint16_t clear;
	for(;;){
		activationDelCapteur();
		activationFiltreRouge();
		red = Mesure();
		activationFiltreBleu();
		bleu = Mesure();
		activationFiltreVert();
		vert = Mesure();
		activationFiltreClear();
		clear =Mesure();
		//clear =0;
		if (red < 5000 && clear > 5000 && vert > 10000 ) 
			PORTB=0x01;

		else if (bleu > 3000 && clear > 5000 && vert > 10000) 
			PORTB =0x00;

		else if ( vert < 8300 && clear > 6000 && red > 5000 && bleu < 3500 ) 
			PORTB =0x02;

		else if (clear < 5000)
		  PORTB=0x00;	

		
		
	}
}


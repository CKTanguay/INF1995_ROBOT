
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
	uint8_t SIZEMAX=100;
	char TableauForme[3]={'R','V','B'};   // tableau de forme remplie par le capteur distance	
	char TabLectureDonnees[SIZEMAX][3]; //tableau dans lequel on mettera nos lecture de couleur
	bool formFound=false;
	int i=0;
	while(formFound==false)
	{
		activationDelCapteur();	
		activationFiltreRouge();
		red = Mesure();
		activationFiltreBleu();
		bleu = Mesure();
		activationFiltreVert();
		vert = Mesure();
		activationFiltreClear();
		clear =Mesure();
		int j=0;
		while(j<3)
		{
			if (red < 5000 && clear > 5000 && vert > 10000 ) 
			{
				PORTB=0x01;
				TabLectureDonnees[i][j]='R';
				j++;
			}	

			else if (bleu > 3000 && clear > 5000 && vert > 10000) 
			{
				PORTB=0x02;
				TabLectureDonnees[i][j]='B';
				j++;
			}	
			else if ( vert < 8300 && clear > 6000 && red > 5000 && bleu < 3500 ) 
			{
				PORTB=0x00;
				TabLectureDonnees[i][j]='R';
				j++;
			}	
		}
		int cpt=0;
		for(int k=0;k<3;k++)
		{
			if(TabLectureDonnees[i][k]==TableauForme[k])
			{
				cpt++;
			}
		}
		if(cpt==3)
		{
				formFound=true;
		}
		i++;
	}
	
	return 0;
}



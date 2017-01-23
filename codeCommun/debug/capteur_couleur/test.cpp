
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
	bool formeTrouve=false;
	char TabForme[3]={'R','V','B'};
	char TabLecture[3]={};
	
	while(formeTrouve==false) 
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
		int i=0;
		
		while((i<=3) && !(clear < 5000))
		{
			//_delay_ms(1000);
			activationDelCapteur();	
			activationFiltreRouge();
			red = Mesure();
			activationFiltreBleu();
			bleu = Mesure();
			activationFiltreVert();
			vert = Mesure();
			activationFiltreClear();
			clear =Mesure();
			if (red < 5000 && clear > 5000 && vert > 10000 && TabLecture[i-1]!='R') 
			{
				PORTB=0x01;
				TabLecture[i]='R';
				//_delay_ms(1000);
				i++;
			}
			else if (bleu > 3000 && clear > 5000 && vert > 10000 && TabLecture[i-1]!='B') 
			{
				PORTB =0x02;
				TabLecture[i]='B';
				i++;
				//_delay_ms(1000);
			}
			else if ( vert < 8300 && clear > 6000 && red > 5000 && bleu < 3500 && TabLecture[i-1]!='V') 
			{	
				PORTB =0x01;
				TabLecture[i]='V';
				i++;
				//_delay_ms(1000);
			}
			//i++;
			//else if (clear < 5000)
			//{
				//PORTB=0x00;
			//}	
		}
		PORTB=0x00;
		int cpt=0;
		for(int k=0;k<3;k++)
		{
			if(TabForme[k]==TabLecture[k])
				cpt++;
		}	
		if(cpt==3)
			formeTrouve=true;
		
			
	}
	eteindreDelCapteur();
	
	
	return 0;
}



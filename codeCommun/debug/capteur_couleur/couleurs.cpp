#include "couleurs.h"


void activationFiltreRouge(){
	PORTC= filtrePourRouge;
}
void activationFiltreBleu(){
	PORTC = filtrePourBleu;
}
void activationFiltreVert(){
	PORTC=filtrePourVert;
	}
void activationFiltreClear(){
	PORTC = filtrePourClear;
	}
void activationDelCapteur(){
	PORTD = allumerDel;	
	}
void eteindreDelCapteur(){
	PORTD = eteindreDel;	
	}
void partirScalerZero(){
	PORTC= scalerZero;
	}
void partirScalerDeux(){
	PORTC= scalerDeux;
	}
void partirScalerVingt(){
	PORTC= scalerVingt;
	}
void partirScalerCent(){
	PORTC= scalerCent;
	}
	
	
uint16_t Mesure()
{
	
	//uint8_t mask = 0x03;
	while (PIND & 0x02){}
	while(!(PIND & 0x02)){}  //pendant 0 w8
   TCNT1=0x00;
   TCCR1B=0x01; //prescallor de 1
   TCCR1A=0x00;  
   while (PIND & 0x02){}
   while(!(PIND& 0x02)){}   //compte jusqua 1
   while(PIND & 0x02){}   //compte jusqua 0 ce qui represente 1 cycle
   TCCR1B=0x00; // arete timer
   return TCNT1;
}

bool bonneSerieCouleur(char TabForme[3])
 {
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
	char TabForme[3]={'R','V','B'}; //juste pour tester
	char TabLecture[3]={}; //tableau ou on met nos lecture
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
				i++;
			}
			else if (bleu > 3000 && clear > 5000 && vert > 10000 && TabLecture[i-1]!='B') 
			{
				PORTB =0x02;
				TabLecture[i]='B';
				i++;
			}
			else if ( vert < 8300 && clear > 6000 && red > 5000 && bleu < 3500 && TabLecture[i-1]!='V') 
			{	
				PORTB =0x01;
				TabLecture[i]='V';
				i++;
			}
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
	return formeTrouve;
}

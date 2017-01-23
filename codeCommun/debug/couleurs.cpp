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

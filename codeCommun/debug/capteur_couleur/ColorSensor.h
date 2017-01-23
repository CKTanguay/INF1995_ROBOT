#include <avr/io.h>
#include <stdint.h>
#ifndef  F_CPU
#define  F_CPU  8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define maskFiltre 0xF3
#define filtrePourRouge (((PORTC & maskFiltre) | 0x00)) 
#define filtrePourBleu  (((PORTC & maskFiltre) | 0x08)) 
#define filtrePourVert (((PORTC & maskFiltre) | 0x0C)) 
#define filtrePourClear (((PORTC & maskFiltre) | 0x04)) 
#define maskDel 0xFE
#define allumerDel ((PORTD & maskDel) | 0x01)
#define eteindreDel ((PORTD & maskDel) | 0x00)  
#define maskScaler 0xFC
#define scalerZero ((PORTC & maskScaler) | 0x00)
#define scalerDeux ((PORTC & maskScaler) | 0x02)
#define scalerVingt ((PORTC & maskScaler) | 0x01)
#define scalerCent ((PORTC & maskScaler) | 0x03)

class CapteurCouleur
{
public:
	CapteurCouleur();
	~CapteurCouleur();
	
	void activationFiltreRouge();
	void activationFiltreBleu();
	void activationFiltreVert();
	void activationFiltreClear();
	void activationDelCapteur();
	void eteindreDelCapteur();
	void partirScalerZero();
	void partirScalerDeux();
	void partirScalerVingt();
	void partirScalerCent();
	
	uint16_t Mesure();
	bool bonneSerieCouleur(char TabForme[3]); // prend en parametre le tableau construit dans capteur distance
		
		
private:
	char TableauLecture_[3];
		
	
};
#endif

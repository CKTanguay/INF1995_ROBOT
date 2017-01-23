#ifndef  CAPTEURCOULEUR_H
#define  CAPTEURCOULEUR_H
#include <avr/io.h>
#include <stdint.h>
#ifndef  F_CPU
#define  F_CPU  8000000UL
#endif
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Piezo.h"

#define maskFiltre 0xF3
#define filtrePourRouge (((PORTC & maskFiltre) | 0x00)) 
#define filtrePourBleu  (((PORTC & maskFiltre) | 0x08)) 
#define filtrePourVert (((PORTC & maskFiltre) | 0x0C)) 
#define filtrePourClear (((PORTC & maskFiltre) | 0x04)) 
#define maskDel 0xFB
#define allumerDel ((PORTD & maskDel) | 0x04)
#define eteindreDel ((PORTD & maskDel) | 0x00)  
#define maskScaler 0xFC
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
	void partirScalerCent();
	
	uint16_t Mesure();
    char identifierCouleurScalerCent();
    char identifierCouleurMoyenne(int nbMesures);
		
};
#endif

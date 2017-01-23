#include "pwm_moteur.h"

void partirPwmMoteursPourc(float pourcentageLeft, float pourcentageRight) {
	float valeurTimerLeft= ((pourcentageLeft/100)*255);
	float valeurTimerRight= ((pourcentageRight/100)*255);
	TCNT0 = 0;  // cpt commence a 0
	OCR0A = valeurTimerLeft;   // valeur de comparaison moteur gauche
	OCR0B = valeurTimerRight;  // valeur de comparaison moteur droit
	TCCR0A = 0xA3; 			   // fast pwm  
	TCCR0B = 0x03;             // prescaler 1024  
}
void partirPourc(float pourcentageLeft, float pourcentageRight) {
	float valeurTimerLeft= ((pourcentageLeft/100)*255);
	float valeurTimerRight= ((pourcentageRight/100)*255);  // cpt commence a 0
	OCR0A = valeurTimerLeft;   // valeur de comparaison moteur gauche
	OCR0B = valeurTimerRight;  // valeur de comparaison moteur droit
	TCCR0A = 0xA3; 			   // fast pwm  
	TCCR0B = 0x03;             // prescaler 1024  
} 

void partirPwmMoteursValeur(uint8_t valeurTimerLeft, uint8_t valeurTimerRight) {
	TCNT0 = 0; 
	OCR0A = valeurTimerLeft;
	OCR0B = valeurTimerRight;
	TCCR0A = 0xA3; 
	TCCR0B = 0x03;  
}

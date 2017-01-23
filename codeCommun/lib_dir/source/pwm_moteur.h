#ifndef PWM_MOTEUR_H
#define PWM_MOTEUR_H
//#ifndef F_CPU 
# define F_CPU 8000000UL

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

void partirPwmMoteursPourc(float pourcentageLeft, float pourcentageRight);
	
void partirPourc(float pourcentageLeft, float pourcentageRight);

void partirPwmMoteursValeurwmMoteursValeur(uint8_t valeurTimerLeft, uint8_t valeurTimerRight);

#endif



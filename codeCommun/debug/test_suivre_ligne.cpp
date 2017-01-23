
#include <avr/io.h>
#include <stdint.h>
#ifndef 	F_CPU
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include "Del.h"
#include "FonctionDelai.h"
#include "Piezo.h"
#include "musique.cpp"

#include "memoire_24.h"
#include "pwm_moteur.cpp"

// valeurs de reception des capteurs
#define capteur1 0x02
#define capteur2 0x01
#define capteur3 0x08
#define capteur4 0x04
#define capteur5 0x20
//combinaison des capteurs
#define capteurs1_2 0x03
#define capteurs1_2_3 0x0B
#define capteurs1_2_3_4 0x0D


#define capteurs2_3 0x05
#define capteurs3_4 0x0C
#define capteurs4_5 0x28
#define capteurs3_4_5 0x2C
#define capteurs2_3_4_5 0x2D
#define capteurs1_2_3_4_5 0x2f





int main (){
	TCNT0=0;
	DDRA=0x00;
	DDRD=0x00;
	DDRB=0xff;
	uint8_t Vitesse =100;

	for(;;){
		uint8_t bitsCapteur= (0x2f & PINA);
		switch (bitsCapteur){
			case capteur3: //foward
			partirPourc(Vitesse,Vitesse);
			break;
			
		case capteur2: // correction vers la gauche
			partirPourc(60,100);
			break;
			
		case capteur4: // correction vers la droite
			partirPourc(100,50);
			break;

		default:  // lorsquil est perdu
			partirPourc(40, 0);
			break;
			
		case capteurs4_5:
		case capteurs3_4_5:
		case capteurs2_3_4_5:
		case capteurs1_2_3_4_5:
		PORTB = 0x24;
		partirPourc(80,80);
		_delay_ms(250);
		PORTB=0x00;
		partirPourc(80,20);
		_delay_ms(350);
			while (bitsCapteur!=capteur3){
				
				bitsCapteur= (0x2f & PINA);
				partirPourc(80,20);
				}
				
		break;
		case capteurs1_2:
		case capteurs1_2_3:
		case capteurs1_2_3_4:
			PORTB = 0x24;
			partirPourc(80,80);
			_delay_ms(250);
			PORTB=0x00;
			partirPourc(20,80);
			_delay_ms(350);
			while (bitsCapteur!=capteur3){
				bitsCapteur= (0x2f & PINA);
				partirPourc(20,80);
			}
		break;
		}
	}
return 0;
}

#endif

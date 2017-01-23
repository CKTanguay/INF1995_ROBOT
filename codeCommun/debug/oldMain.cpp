
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
#define capteurs3_2_1 0x0B
#define capteurs1_2_3_4 0x0D
#define capteurs3_2 0x05
#define capteurs3_4 0x0C
#define capteurs4_5 0x28
#define capteurs3_4_5 0x2C
#define capteurs2_3_4_5 0x2D
#define capteurs1_2_3_4_5 0x2F

/*Pour le parcours demandé, on sait que le robot aura à tourner 5 fois sur la droite, 1 fois sur la gauche et ne plus tourner.*/ 

int main (){
	TCNT0=0;
	DDRA=0x00;
	DDRD=0x00;
	DDRB=0xff;
	float Vitesse =60; // Vitesse "normale" 60
	bool depart = true; // Variable déterminant si le robot est en position de départ
	uint8_t compteurDroite = 0; // nombre de virage à droite
	bool tournant = true; // variable controlant l'autorisation du robot à tourner

	for(;;)
	{
		uint8_t bitsCapteur= (0x2f & PINA);
		
		switch (bitsCapteur)
		{
			case capteur3: //foward
				partirPourc(Vitesse, Vitesse);
				break;
				
			case capteur1:
				//correction forte vers la gauche
				PORTB = 0x04; // on inverse la roue gauche
				partirPourc(Vitesse, Vitesse);
				PORTB= 0x00; //les roues reprennent leurs fonctionnements normals
				break;
			
			case capteur2: // correction vers la gauche
				partirPourc(Vitesse/1.7, Vitesse);
				break;
				
			case capteur4: // correction vers la droite
				partirPourc(Vitesse, Vitesse/1.7);
				break;
				
			case capteur5:
				//correction forte vers la droite 
				PORTB = 0x20; // on inverse la roue gauche
				partirPourc(Vitesse, Vitesse);
				PORTB= 0x00; //les roues reprennent leurs fonctionnements normals
				break;
	
			case capteurs1_2_3_4_5: // tourne à droite si il a le choix entre droite et gauche
				if(depart)
				{
					partirPourc(Vitesse, Vitesse);
					delai500MS(1);
					depart = false;
					break;
				}
								
			case capteurs2_3_4_5:	
			case capteurs3_4_5:
			case capteurs4_5:
				if(tournant)
				{
					compteurDroite++;
					partirPourc(Vitesse,Vitesse); // le robot avance pendant un temps prédéfini
					delai100MS(10);
					PORTB = 0x24; // on recule pendant un cours instant pour compenser l'inertie
					delai25MS(4);
					PORTB = 0x20; // on inverse la roue droite
					partirPourc(Vitesse, Vitesse); // le robot pivote pendant un temps prédéfini
					delai100MS(7);
					while (bitsCapteur!=capteur5) // le robot pivote tant que le capteur à l'extrémité droite n'est pas actif 
					{
						bitsCapteur= (0x2f & PINA); // on relit la valeur du capteur
					}
					PORTB = 0x00; // les roues reprennent leurs fonctionnements normals
					partirPourc(0, 0); // on arrête le moteur pour compenser l'inertie de rotation
					delai100MS(6);
					break;
				}

				
				
			case capteurs1_2_3_4:
			case capteurs3_2_1:
			case capteurs1_2:
				if(compteurDroite > 4 && tournant) // si on a tourner au moins 5 fois à droite et si le robot est autorisé à tourner
				{
					tournant = false; // le premier virage à gauche est le dernier virage
					partirPourc(Vitesse,Vitesse); // le robot avance pendant un temps prédéfini
					delai100MS(10);
					PORTB = 0x24; // on recule pendant un cours instant pour compenser l'inertie
					delai25MS(4);
					PORTB = 0x4; // on inverse la roue gauche
					partirPourc(Vitesse, Vitesse); // le robot pivote pendant un temps prédéfini
					delai100MS(7);
					while (bitsCapteur!=capteur1) // le robot pivote tant que le capteur à l'extrémité gauche n'est pas actif 
					{
						bitsCapteur= (0x2f & PINA);
					}
					PORTB = 0x00; // les roues reprennent leurs fonctionnements normals.
					partirPourc(0, 0); // on arrête le moteur pour compenser l'inertie de rotation
					delai100MS(6);
					break;
				}
				
			default:
				partirPourc(Vitesse,Vitesse/1.5);
		}
	}
	
	
	return 0;
}


#endif

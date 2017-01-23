#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include "Del.h"
#include "FonctionDelai.h"
#include "Piezo.h"
#include "musique.cpp"

#include "memoire_24.h"
#include "pwm_moteur.cpp"


#define DBT  0x01	// début
#define ATT  0x02	// attendre
#define DAL  0x44	// allumer la DEL
#define DET  0x45	// éteindre la DEL
#define SGO  0x48	// jouer une sonorité
#define SAR  0x09	// arrêter de jouer la sonorité
#define MAR0 0x60	// arrêter les moteurs		//REVOIR CAR SI ON FAIT MAR1 JUSTE LE 1 ARRETE
#define MAR1 0x61	// arrêter les moteurs		//////
#define MAV  0x62	// avancer
#define MRE  0x63	// reculer
#define TRD  0x64	// tourner à droite
#define TRG  0X65	// tourner à gauche
#define DBC  0xC0	// début de boucle
#define FBC  0xC1	// fin de boucle
#define FIN  0xFF	// fin


int main(){
	DDRB = 0xff;    
    DDRD = 0x00;
        
    
	while (PIND & 0x04){} // rajouter un vrai test avec le bouton poussoir
	Memoire24CXXX mem;
	uint16_t adresseCourante = 0x02; // on commence la lecture après l'indication
									// sur le total de nombre d'octet
	uint8_t ancienneAdresse;
	uint8_t instruction;
	uint8_t operande;
	uint16_t nbBoucle;
	Piezo piezo;
	Del del;

	while (instruction != 0xff)
	{
		mem.lecture(adresseCourante, &instruction); // lecture de l'instruction
		adresseCourante++;
		mem.lecture(adresseCourante, &operande); // lecture de l'opérande
		adresseCourante++;	
		switch(instruction){
		case(DBT): // début
			del.allumerR();
			delai25MS(50);
			del.eteindre();
			delai25MS(50);
			del.allumerV();			
			delai25MS(50);
			del.eteindre();
			break;

		case(ATT):	
		
		delai25MS(operande);
		
			break;
		case(DAL):// allumer la DEL
				switch(operande){
					case(0x01):
					del.allumerR();
					break;
					case(0x02):
					del.allumerV();
					break;	
					}
			break;

		case(DET): // éteindre la DEL
			del.eteindre();	
			break;

		case(SGO):
			piezo.initialisation();
			piezo.jouerSon(operande);
			//delai25MS(500);
			break;

		case(SAR):
			piezo.arreterSon();


			break;

		case(MAR0):	


		case(MAR1):
			partirPwmMoteursValeur(0, 0);

			break;

		case(MAV):
			PORTB=0x00;
			partirPwmMoteursValeur(operande, operande);	
			break;

		case(MRE):
			PORTB = 0x24;
			partirPwmMoteursValeur(operande, operande);
			break;

		case(TRD):
			PORTB=0x00;
			partirPwmMoteursValeur(0, 0);
			delai250MS(3);
			PORTB = 0x20;
			partirPwmMoteursPourc(66,43);
			delai250MS(5);
			partirPwmMoteursValeur(0, 0);
			delai250MS(1);
			

			break;

		case(TRG):
			PORTB=0x00;
			partirPwmMoteursValeur(0, 0);
			delai250MS(3);
			PORTB = 0x04;
			partirPwmMoteursPourc(44,68);
			delai250MS(5);
			partirPwmMoteursValeur(0, 0);
			delai250MS(1);
			

			break;

		case(DBC):	// début de boucle
			ancienneAdresse = adresseCourante;	// enregistrement de l'adresse courante 
												// de la prochaine instruction			
			nbBoucle = operande;	
			break;

		case(FBC): // fin de boucle
		if(nbBoucle > 0)
		{
			adresseCourante = ancienneAdresse; // réaffectation de l'adresse courante
			nbBoucle--; 
		}
			break;

		case(FIN):
		musique();
		
			break;
		}
	}
}
	
	



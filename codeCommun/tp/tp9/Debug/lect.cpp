#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>


#include "memoire_24.h"


#define DBT  0x01	//début
#define ATT  0x02	//attendre
#define DAL  0x44	//allumer la DEL
#define DET  0x45	//éteindre la DEL
#define SGO  0x48	//jouer une sonorité
#define SAR  0x09	//arrêter de jouer la sonorité
#define MAR0 0x60	//arrêter les moteurs		//REVOIR CAR SI ON FAIT MAR1 JUSTE LE 1 ARRETE
#define MAR1 0x61	//arrêter les moteurs		//////
#define MAV  0x62	//avancer
#define MRE  0x63	//reculer
#define TRD  0x64	//tourner à droite
#define TRG  0X65	//tourner à gauche
#define DBC  0xC0	//début de boucle
#define FBC  0xC1	//fin de boucle
#define FIN  0xFF	//fin


int main(){
	DDRB = 0xff;    
    DDRD = 0x00;
	while (PIND & 0x04){}
	Memoire24CXXX mem;
	uint8_t nbInst;
	uint8_t adresseCourante= 0x00;
	const uint8_t adresseInitiale=0x00;

	mem.lecture(adresseInitiale+1, &nbInst);
	adresseCourante += 0x02;
	uint8_t instruction;
	uint8_t operande;
	while (instruction != 0xff)
	{
		mem.lecture(adresseCourante, &instruction);
		adresseCourante++;
		mem.lecture(adresseCourante, &operande);
		adresseCourante++;
		
		
		switch(instruction){
		case(DBT):
		
			break;

		case(ATT):	switch(operande){
					case(0x50):
					_delay_ms(2000);
					break;
					case(0x28):
					_delay_ms(1000);
					break;	
					}
			break;
		case(DAL):
				switch(operande){
					case(0x01):PORTB=0x01;
					break;
					case(0x02):PORTB=0x02;
					break;	
					}
			break;

		case(DET):
			PORTB=0x00;	//pt  utiliser les fonctions dans la librairie et specifier quel port
			break;

		case(SGO):

			break;

		case(SAR):

			break;

		case(MAR0):		//**Pas de break ici, car on veut arreter les deux moteurs**// --> REVOIR


		case(MAR1):

			break;

		case(MAV):

			break;

		case(MRE):

			break;

		case(TRD):

			break;

		case(TRG):

			break;

		case(DBC):

			break;

		case(FBC):

			break;

		case(FIN):

			break;
		}
	}
}
	
	



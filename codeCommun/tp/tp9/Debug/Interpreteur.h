
#ifndef F_CPU
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <Del.h>
#include <memoire_24.h>
#include <LectureMemoire.h>
#include <FonctionDelai.h>


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


class Interpreteur
{
public:
	Interpreteur();

	void Interpretation();


private:


};

#endif

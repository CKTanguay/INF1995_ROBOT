/* Auteurs : Tom Avedissian et Christophe Kedzierski-Tanguay
 * Date de création : 25/11/2016
 * Description : La classe robot permet de controler les mouvements du robot*/

#ifndef ROBOT_H
#define ROBOT_H
#define capteur1 0x02
#define capteur5 0x20

#include "CapteurDistance.h"
#include "Del.h"
#include "pwm_moteur.h"
#include "FonctionDelai.h"
#include "CapteurCouleur.h"
#include "Piezo.h"



class Robot
{
public:
	
	Robot();
	Robot(float vitesse);
	
	~Robot();
	
	void avancer() const;
	void demarrer();
	void arreter() const;

	bool obtenirDepart() const;
	
	uint8_t obtenirBitsCapteur() const;
	void lireBitsCapteur();
	
	void modifierVitesse(float vitesse);

	void tournerDroite(); 
	void tournerGauche();
	
	void correctionGauche() const;
	void correctionForteGauche() const;
	
	void correctionDroite() const;
	void correctionForteDroite() const;
		
	void initialisationUART();
	void transmissionUART(uint8_t nombre8Bit);
	
	bool obstacleEstProche();	
	char identifierPiece();
	
	void jouerSon();
	void arreterSon();
	
	char identifierCouleur(int nbMesures);
	void eteindreDelCapteur();
	
private:
	float vitesse_;
	uint8_t bitsCapteur_;
	bool depart_; // Variable déterminant si le robot est en position de départ
	CapteurDistance capteurDistance_;
	CapteurCouleur capteurCouleur_;
	Del del_;
};
	
#endif

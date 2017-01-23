#include <avr/io.h>
#include <stdint.h>
#include "Robot.h"

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
#define capteurs4_5 0x24
#define capteurs3_4_5 0x2C
#define capteurs2_3_4_5 0x2D
#define capteurs1_2_3_4_5 0x2F

/*Pour le parcours demandé, on sait que le robot aura à tourner 5 fois sur la droite, 1 fois sur la gauche et ne plus tourner.*/ 
//largeur salle=60cm (60.5)
//distance entre capteur de distance et point de pivot du robot =11.5

int main ()
{	

	Robot robot(55);
	bool tournant = true; 					// variable controlant l'autorisation du robot à tourner
	uint8_t compteurDroite = 0; 			// nombre de virage à droite
	bool detectionPermise = false;
	char tabSequencePieces[3]; // tableau remplit à l'envers
	char tabSequenceCouleurs[3];
	uint8_t indexTabPieces = 2; // on commence par remplir la position 2;
	uint8_t indexTabCouleurs =0;
	Piezo::initialisation();
	Piezo::arreterSon();
	char lastFoo = 'm';
	//test temps
	uint8_t compteur =0;
	bool bonNbMesure = false;
	char lFoo ='a';
	//
	while(true)
	{
		robot.lireBitsCapteur();
		
		if(compteurDroite % 2 != 0 && detectionPermise) 				// à chaque virage à droite impair
		{
			if(robot.obstacleEstProche())
			{
				robot.arreter();
				tabSequencePieces[indexTabPieces] = robot.identifierPiece();
				indexTabPieces --;
				detectionPermise = false;
			}
		}

		if(tournant==false)
		{
			char foo = robot.identifierCouleur(3);
			if (foo == lFoo){
				compteur++;
				lFoo =foo;
			}
			
			else if (foo != lFoo){
				compteur =0;
				lFoo =foo;
			}
			
			if (compteur ==15){
				bonNbMesure =true;
				compteur =0;
				}
			if (bonNbMesure)
				{
				if (foo == 'c' || indexTabCouleurs == 2){
					tabSequenceCouleurs[0] = 'm'; 
					tabSequenceCouleurs[1] = 'm';
					tabSequenceCouleurs[2] = 'm';  // inutile (securiter de plus)
					indexTabCouleurs = 0;
				}
				else if (foo != lastFoo &&foo != 'c'){
						tabSequenceCouleurs[indexTabCouleurs]=foo;
						indexTabCouleurs++;
						
					}
				
				if ( tabSequenceCouleurs[0] == tabSequencePieces[0] && tabSequenceCouleurs[1] == tabSequencePieces[1]){
					Piezo::arreterSon();
					robot.eteindreDelCapteur();
					robot.arreter();
					return 0;
				}
				lastFoo= foo;  
			}    bonNbMesure=false;  
		}
		
		switch (robot.obtenirBitsCapteur())
		{
			case capteur3:					// avancer
				robot.avancer();
				break;
				
			case capteur1:					// correction forte vers la gauche
				robot.correctionForteGauche();
				break;
			
			case capteur2:					// correction vers la gauche
				robot.correctionGauche();
				break;
				
			case capteur4:					// correction vers la droite
				robot.correctionDroite();
				break;
				
			case capteur5:					// correction forte vers la droite 
				robot.correctionForteDroite();
				break;
	
			case capteurs1_2_3_4_5: 		// le robot tourne à droite
				if(robot.obtenirDepart()) 			// si le départ n'a pas eu lieu
				{
					robot.demarrer();
					break;
				} 
			case capteurs2_3_4_5:	
			case capteurs3_4_5:
			case capteurs4_5:
				if(tournant)
				{
					detectionPermise = true;
					compteurDroite++;
					robot.tournerDroite();
				}
				break;

			case capteurs1_2_3_4: 					// le robot tourne à gauche
			case capteurs3_2_1:
			case capteurs1_2:
				if(compteurDroite > 4 && tournant) 	// si on a tourner au moins 5 fois à droite et si le robot est autorisé à tourner
				{
					tournant = false; 				// le premier virage à gauche est le dernier virage
					robot.tournerGauche();				
				}
				break;
				
			default:
				robot.avancer();
		}
	}
	robot.arreter();
	return 0;
}

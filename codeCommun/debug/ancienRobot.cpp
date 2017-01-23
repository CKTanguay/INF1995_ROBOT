#include "Robot.h"

Robot::Robot() : vitesse_(60), depart_(true)
{
	TCNT0=0; 	// compteur0 mis à 0
	DDRA=0x00; 	// Port A en entrée
	DDRD=0x00; 	// Port D en entrée
	DDRB=0xff; 	// Port B en sortie
	bitsCapteur_= 0x00;
	//CapteurDistance capteurDistance_;
};

Robot::Robot(float vitesse): vitesse_(vitesse), depart_(true)
{
	TCNT0=0; 	// compteur0 mis à 0
	DDRA=0x00; 	// Port A en entrée
	DDRD=0x00; 	// Port D en entrée
	DDRB=0xff; 	// Port B en sortie
	bitsCapteur_= 0x00;
};

Robot::~Robot() {};

void Robot::avancer() const
{
	partirPourc(vitesse_, vitesse_);
};

void Robot::demarrer()
{
	avancer();
	delai100MS(7);
	depart_ = false; // on signale que le départ a eu lieu
}

void Robot::arreter() const
{
	partirPourc(0,0);
}

bool Robot::obtenirDepart() const
{
	return depart_;
}

uint8_t Robot::obtenirBitsCapteur() const 
{
	return bitsCapteur_;
}

void Robot::tournerDroite()
{
	lireBitsCapteur();  				// on relit la valeur du capteur
	partirPourc(vitesse_,vitesse_); 	// le robot avance pendant un temps prédéfini
	delai100MS(13);
	PORTB = 0x24; 						// on recule pendant un cours instant pour compenser l'inertie
	delai100MS(1);
	PORTB = 0x20; 						// on inverse la roue droite
	delai100MS(3);
	
	while (bitsCapteur_!=capteur5) 		// le robot pivote tant que le capteur à l'extrémité droite n'est pas actif 
	{
		lireBitsCapteur(); 				// on relit la valeur du capteur
	}
	PORTB = 0x00; 						// les roues reprennent leurs fonctionnements normals
	arreter(); 					// on arrête le moteur pour compenser l'inertie de rotation
	delai100MS(6);

};
	
	
void Robot::tournerGauche()
{
	lireBitsCapteur();					// on relit la valeur du capteur
	avancer();							// le robot avance pendant un temps prédéfini
	delai100MS(13);
	PORTB = 0x24; 						// on recule pendant un cours instant pour compenser l'inertie
	delai100MS(1);
	PORTB = 0x04; 						// on inverse la roue gauche
	delai100MS(3);
	
	while (bitsCapteur_!=capteur1) 		// le robot pivote tant que le capteur à l'extrémité gauche n'est pas actif 
	{
		lireBitsCapteur(); 
	}
	
	PORTB = 0x00; 						// les roues reprennent leurs fonctionnements normals.
	arreter(); 							// on arrête le moteur pour compenser l'inertie de rotation
	delai100MS(6);
};


void Robot::modifierVitesse(float vitesse)
{
	vitesse_ = vitesse;
};

void Robot::lireBitsCapteur()
{
	bitsCapteur_=(0x2f & PINA);
}


void Robot::correctionGauche() const
{
	partirPourc(vitesse_/1.8, vitesse_);
};


void Robot::correctionForteGauche() const
{
	PORTB = 0x04; // on inverse la roue gauche
	avancer();
	PORTB= 0x00; //les roues reprennent leurs fonctionnements normals
};


void Robot::correctionDroite() const
{
	partirPourc(vitesse_, vitesse_/1.8);
};


void Robot::correctionForteDroite() const
{
	PORTB = 0x20; // on inverse la roue gauche
	avancer();
	PORTB= 0x00; //les roues reprennent leurs fonctionnements normals
};


void Robot::initialisationUART()
{
	capteurDistance_.initialisationUART();
}


void Robot::transmissionUART(uint8_t nombre8Bit)
{
	capteurDistance_.transmissionUART(nombre8Bit);
}


bool Robot::obstacleEstProche()
{
	return(capteurDistance_.obstacleEstProche());
}


char Robot::identifierPiece()
{
	initialisationUART();
	int reference=capteurDistance_.distanceMoyenneMesuree(64);	//64 est le nombre de mesures prises durant un cycle
	int max= reference;
	int min= reference;
	int valeurMoyenneMesuree=0;
	int somme =0;
	bool sensCroissant=true;
	int var1=0;
	lireBitsCapteur();  				// on initialise la valeur de bitsCapteur_
	int ancienneValeurMoyenneMesuree = reference;
	// séquence de mesure
	PORTB = 0x20;						// inversion de la roue droite	
	delai500MS(1); 			
	for (int i=0; i<24; i++)			//18 est le nombre de cycles de mesure
	{	
		partirPourc(78,78);
		delai25MS(6);
		arreter();
		delai100MS(3);
		valeurMoyenneMesuree = capteurDistance_.distanceMoyenneMesuree(128);
			
		if(valeurMoyenneMesuree > max)
			max=valeurMoyenneMesuree;
			
		else if(valeurMoyenneMesuree < min)
			min=valeurMoyenneMesuree;
		
		if (sensCroissant && ancienneValeurMoyenneMesuree > (valeurMoyenneMesuree+2)){
			var1++;
			sensCroissant = false;	
		}	
		
		if (!sensCroissant && (ancienneValeurMoyenneMesuree+2) < valeurMoyenneMesuree){
			var1++;
			sensCroissant = true;	
		}
		
		ancienneValeurMoyenneMesuree =valeurMoyenneMesuree; 	
		
		transmissionUART(var1);	
	}
	
	
	//on finit le demi-tour amorcé durant la détection
	avancer(); 								// le robot avance pendant un temps prédéfini
	
	while (bitsCapteur_!=capteur5) 			// le robot pivote tant que le capteur à l'extrémité droite n'est pas actif 
	{
		lireBitsCapteur(); 					// on relit la valeur du capteur
	}
	
	PORTB = 0x00; 							// les roues reprennent leurs fonctionnements normals
	arreter(); 								// on arrête le moteur pour compenser l'inertie de rotation
	delai100MS(6);	
	
	if ((max - min) > 40)		// Carré
	{
		jouerSon();
		delai1000MS(2);
		arreterSon();
		return 'b';							//on detecte la salle carrée
	}
	
	else if (var1 > 4) 						// Octogone
	{
		del_.allumerR();
		delai1000MS(2);
		del_.eteindre(); 
		return 'r';							//on detecte la salle octogonale
	}
	
	else 									// Cercle
	{
		del_.allumerV();
		delai1000MS(2);
		del_.eteindre(); 
		return 'v';							//on detecte la salle circulaire // entre 30 et 75
	} 
}


void Robot::jouerSon()
{
	Piezo::initialisation();
	Piezo::jouerSonAigu();
}


void Robot::arreterSon()
{
	Piezo::arreterSon();
}

char Robot::identifierCouleur (int nbMesures){
	return capteurCouleur_.identifierCouleurMoyenne(nbMesures);
	
	
	}
void Robot::eteindreDelCapteur(){
	capteurCouleur_.eteindreDelCapteur();
	}

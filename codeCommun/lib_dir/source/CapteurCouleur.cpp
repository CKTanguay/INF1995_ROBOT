#include "CapteurCouleur.h"


CapteurCouleur::CapteurCouleur(){}

CapteurCouleur::~CapteurCouleur(){}

//Met la bonne valeur au PORT C pour activer le filtre désiré. 
void CapteurCouleur::activationFiltreRouge()
{
	PORTC= filtrePourRouge;
}

void CapteurCouleur::activationFiltreBleu()
{
	PORTC = filtrePourBleu;
}

void CapteurCouleur::activationFiltreVert()
{
	PORTC=filtrePourVert;
}

void CapteurCouleur::activationFiltreClear()
{
	PORTC = filtrePourClear;
}

void CapteurCouleur::activationDelCapteur()
{
	PORTD = allumerDel;	
}

void CapteurCouleur::eteindreDelCapteur()
{
	PORTD = eteindreDel;	
}

//Met la bonne valeur au PORT C pour sélectionner le "scaler" désiré dans notre cas c'est un "scaler d cent que nous voulons". 
void CapteurCouleur::partirScalerCent()
{
	PORTC= scalerCent;
}
// La méthode Mesure permet de calculer le temps d'un cycle plus le temps d'un actif haut.
// Il active la minutrie au front montant et l'arrête au 2e front decendant. Puis, il retourne la valeur du comteur.
uint16_t CapteurCouleur::Mesure()
{
   while (PIND & 0x08){}
   while(!(PIND & 0x08)){}  
   TCNT1=0x00;                      //On active la minutrie en mode normal avec un prescalor de 1.
   TCCR1B=0x01; 
   TCCR1A=0x00;  
   while (PIND & 0x08){}            // actif haut 1
   while(!(PIND& 0x08)){}           // actif bas 1
   while(PIND & 0x08){}             //actif haut 2
   TCCR1B=0x00;                     // arrête la minutrie.
   return TCNT1;
}

// On prend des mesures avec tous les filtres. Ensuite, on les compares avec des valeur de références afin de déterminer la couleur.
// un char corespondant à la première lettre de la couleur est retournée.
char CapteurCouleur::identifierCouleurScalerCent()
{
	
    DDRC=0xff;
	DDRB=0xff;
	DDRD|=0x04;
	DDRD |= (1 << DDD6) | (1 << DDD7); // On s'assure que les pins 4 et 5 du port D sont en mode sortie pour intérompe le piezo.
	
	partirScalerCent();
	
    uint16_t red;
	uint16_t bleu;
	uint16_t vert;
	uint16_t clear;

	activationDelCapteur();	
	activationFiltreRouge();
	red = Mesure();
	activationFiltreBleu();
	bleu = Mesure();
	activationFiltreVert();
	vert = Mesure();
	activationFiltreClear();
	clear =Mesure();

	
	if (red < 2000 && clear > 1500)
		return 'r';
		
	else if (bleu > 900 && vert > 3000)
			return 'b';
	else if (vert < 3000 && clear >1500)
		return 'v';
	else if (clear < 2000)
		return 'c';

}
// La méthode vérifie si une couleur est retournee un certain nombre de fois, ensuite applique les opérations corespondant à cette couleur, puis la retourne.   
char CapteurCouleur::identifierCouleurMoyenne(int nbMesures){

	char couleurRetour;
	char couleurTemporaire ='m';                //  pour but de comparaison seulement, 'm' choisi aleatoirement
	int compteur =0;                           // compte le nombre de valeur de suite pareil 
	bool mesureIncomplete = true;              // condition while
	while (mesureIncomplete)                   // while qu'il na pas lu nbMesures pareil de suite il ne retourne rien.
	{

		couleurRetour = identifierCouleurScalerCent();

		if (couleurRetour== couleurTemporaire){
			compteur ++;
			}
		if ( compteur == nbMesures){
			mesureIncomplete =false;
			}
		couleurTemporaire = couleurRetour;		
		}
		switch (couleurRetour){
			case 'r': 
					Piezo::arreterSon();
					PORTB=0x01;
					break;
			
			case 'b':
					PORTB=0x00;
					Piezo::jouerSonAigu();
					break;
			case 'v':
					Piezo::arreterSon();
					PORTB=0x02;	
					break;
			case 'c':
					Piezo::arreterSon();
					PORTB=0x00;
					break;
				
				}			
		return couleurRetour; 
}

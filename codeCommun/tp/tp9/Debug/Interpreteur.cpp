#include "Interpreteur.h"

Interpreteur::Interpreteur() {}

void Interpreteur::Interpretation() // pk ta mit const?
{
	//Del del;
	LectureMemoire lect;
	DDRB = 0xff;
	switch(lect.getPtrData().oper)
	{
		case(DBT):
			//del.allumerR();
			PORTB=0x01;
			_delay_ms(1000);
			break;

		case(ATT):	//J'ai fait plusieurs focntions de delai pour pas mal toutes les possibilités,
					//mais si on veut rester plus général on est mieux dy aller avec delai250MS ou
					//delai500MS. CKT
			delai250MS(lect.getPtrData().operande); //Vérifier que la compilation se fait bien ici. CKT
			break;

		case(DAL):

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

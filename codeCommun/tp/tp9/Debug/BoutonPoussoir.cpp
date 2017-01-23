#include "BoutonPoussoir.h"


BoutonPoussoir::BoutonPoussoir():port_(A){}
BoutonPoussoir::~BoutonPoussoir(){}

bool BoutonPoussoir::antiRebond()	//Vérification de l'état du bouton.
{
	if (!(PIND & 0x04))
	{
		_delay_ms(10);
		return (!(PIND & 0x04));
	}
	return false;
}

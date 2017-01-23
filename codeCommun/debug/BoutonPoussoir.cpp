#include "BoutonPoussoir.h"


BoutonPoussoir::BoutonPoussoir():bool_(port){}
BoutonPoussoir::~BoutonPoussoir(){}

bool BoutonPoussoir::antiRebond(const TypePort& port)	//Vérification de l'état du bouton.
{
	if (!(PIND & 0x04))
	{
		_delay_ms(10);
		return (!(PIND & 0x04));
	}
	return false;
}

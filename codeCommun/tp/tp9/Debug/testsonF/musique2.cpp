#include "Piezo.h"

int main()
{
	Piezo piezo;
	piezo.initialisation();
	
	piezo.jouerSon(72);
	_delay_ms(530);
	piezo.jouerSon(76);
	_delay_ms(265);
	piezo.jouerSon(74);
	_delay_ms(265);
	piezo.jouerSon(72);
	_delay_ms(530);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(77);
	_delay_ms(265);
	piezo.jouerSon(76);
	_delay_ms(530);
	piezo.jouerSon(81);
	_delay_ms(265);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(77);
	_delay_ms(265);
	piezo.jouerSon(76);
	_delay_ms(530);
	piezo.jouerSon(74);
	_delay_ms(265);
	piezo.jouerSon(77);
	_delay_ms(132);
	piezo.jouerSon(74);
	_delay_ms(132);
	piezo.jouerSon(72);
	_delay_ms(265);
	piezo.jouerSon(71);
	_delay_ms(265);
	piezo.jouerSon(72);
	_delay_ms(530);
	piezo.jouerSon(76);
	_delay_ms(265);
	piezo.jouerSon(74);
	_delay_ms(265);
	piezo.jouerSon(72);
	_delay_ms(530);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(77);
	_delay_ms(265);
	piezo.jouerSon(76);
	_delay_ms(530);
	piezo.jouerSon(81);
	_delay_ms(265);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(79);
	_delay_ms(265);
	piezo.jouerSon(77);
	_delay_ms(265);
	
	
	piezo.arreterSon();
}



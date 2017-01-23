#include "CapteurDistance.h"


CapteurDistance::CapteurDistance()
{
	nombre8Bit_=0;
	nombre16Bit_=0;
}

CapteurDistance::~CapteurDistance(){}

uint8_t CapteurDistance::getNombre8Bit() const
{
	return nombre8Bit_;
}

void CapteurDistance::initialisationUART()
{
	UBRR0H = 0;
	UBRR0L = 0xCF;
	UCSR0A = 0x00;  
	UCSR0B = 0x18; 
	UCSR0C = 0x06;
}


void CapteurDistance::transmissionUART(uint8_t nombre8Bit)
{
	while(!(UCSR0A & (1 << UDRE0))) {}
	UDR0 = nombre8Bit;
}


bool CapteurDistance::obstacleEstProche()
{
	uint8_t valeurRetourner = distanceMoyenneMesuree(16);

	return(valeurRetourner > 110);	//valeur déterminée lors de tests qui correspond approximativement au milieu de la pièce.
}


int CapteurDistance::distanceMoyenneMesuree(int nombreMesures)
{
	int somme = 0;
	int moyenne;
	
	for (int i= 0; i < nombreMesures; i++) 
	{
		nombre16Bit_=cann_.lecture(7);
		nombre16Bit_ = nombre16Bit_ >> 2;				
		nombre8Bit_ = (nombre16Bit_ & 0x00ff);
		somme += nombre8Bit_;
	}
	
	moyenne=somme/nombreMesures;
	return moyenne;
}

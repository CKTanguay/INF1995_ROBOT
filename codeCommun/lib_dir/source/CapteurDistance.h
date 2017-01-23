#ifndef  CAPTEUR_DISTANCE_H
#define  CAPTEUR_DISTANCE_H
#include <avr/io.h>
#include <stdint.h>
#ifndef  F_CPU
#define  F_CPU  8000000UL
#endif
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

class CapteurDistance
{
public:
	CapteurDistance();
	~CapteurDistance();

	void initialisationUART();
	void transmissionUART(uint8_t nombre8Bit);
	bool obstacleEstProche();
	int distanceMoyenneMesuree(int nombreMesures);
	
	uint8_t getNombre8Bit() const;

private:
	uint8_t nombre8Bit_;
	uint16_t nombre16Bit_;
	can cann_;
	
};


#endif

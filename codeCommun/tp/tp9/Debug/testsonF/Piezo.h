
#ifndef SON_H
#define SON_H

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h> 



class Piezo {
	
public:


	static void jouerSon(uint8_t midi);
	static void arreterSon(void);
	static void initialisation(void);
	void jouerChanson();

private:
	static uint16_t midiTable[37];
	
};
#endif

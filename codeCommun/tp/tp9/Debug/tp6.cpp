
# define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"

int main () {
	DDRB = 0xff;
	Memoire24CXXX memoire;
	uint8_t donnees[]= "*E*C*O*L*E**P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
	bool estpareil = true;
	const uint8_t adresseInitiale=0x00;
	memoire.ecriture(adresseInitiale,donnees, sizeof(donnees)-1);
	_delay_ms(15);
	for (uint8_t i=0; i< (sizeof(donnees)-1); i++){
		uint8_t temp;
	    memoire.lecture(adresseInitiale+i+1, &temp); //temp = out
	    if (temp != donnees[i]){
		PORTB =0x01;
		_delay_ms(100);
		PORTB=0x00;
		estpareil = false;
		}
		if (estpareil){
			PORTB =0x02;
			_delay_ms(1000);
			}
}
	
	
	
	}


# define F_CPU 8000000
#include "memoire_24.h"
#include <avr/io.h>
#include <util/delay.h>

int main(){
	
	uint8_t entree[] = "*E*C*O*L*E**P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
	uint8_t* sortie;
	Memoire24CXXX mem;
	DDRA = 0xff; // mode sortie


	//ecriture
	mem.ecriture(const 0x00,const entree,const 37 ) //entree.length()-1
	//lecture

	bool estEgal = true;
	for (uint16_t i = 0; i < 19 && estEgal; i++){
		mem.lecture(i, sortie);
		if(entree[i] != *sortie){
			estEgal = false;
		}
	}
	
	if (estEgal){
		PORTA = 0x01;

	}else{
		PORTA = 0x02;
	}
	_delay_ms(1000);
	
	PORTA = 0x00;

	
	return 0;
}

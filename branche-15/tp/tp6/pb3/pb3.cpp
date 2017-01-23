# define F_CPU 8000000
#include <avr/io.h>
#include "memoire_24.h"
#include <util/delay.h>


void initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0

//	UCSR0A = 0x00 ;

	// Bits 3 et 4 à 1 pour permettre la reception et la transmission
//	UCSR0B = 0x18;

	// Format des trames: 8 bits, 1 stop bits, none parity
	// Bits 2 et 3 à 1
//	UCSR0C = 0x6 ;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //page 187 doc. Atmel
	UCSR0A = 0x00;
/* Set frame format: 8 bits data, 1 bits stop , without parity */
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

}

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

	while(!( UCSR0A & (1<<UDRE0))){}
	UDR0 = donnee;
}

int main(){
	DDRA = 0xff;
	initialisationUART();
	Memoire24CXXX mem;
	uint8_t i, j;
	uint8_t* mots;
	uint8_t entree[] = "ECOLE POLYTECHNIQUE";
	uint8_t* sortie;
	PORTA = 0x02;
/*
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
	_delay_ms(1000);
	
	
	i = 0x00;
	*/
	for(i = 0; i < 19;i++){
		mem.lecture(i, &mots[i]);	
		PORTA = 0x00;
		_delay_ms(250);
		PORTA =0x02;
		_delay_ms(250);
		transmissionUART(mots[i]);
	}
	
	PORTA = 0x01;
/*	
	for ( i = 0; i < 10; i++ ) {

		for ( j=0x00; j < 20; j++ ) {

			transmissionUART ( mots[j] );

		}

	}
		*/
	PORTA = 0x00;

	
	return 0;
}

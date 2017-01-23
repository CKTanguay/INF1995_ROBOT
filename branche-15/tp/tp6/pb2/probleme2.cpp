# define F_CPU 8000000
#include <avr/io.h>
#include "memoire_24.h"

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
	initialisationUART();
	char mots[21] = "Le robot en INF1995\n";

	uint8_t i, j;

	for ( i = 0; i < 1; i++ ) {

		for ( j=0; j < 20; j++ ) {

			transmissionUART ( mots[j] );

		}

	}
<<<<<<< .mine

=======

	
	
>>>>>>> .r27
	return 0;
}

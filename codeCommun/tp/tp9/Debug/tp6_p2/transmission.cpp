
# define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

UCSR0A = 0x00;  //'modifier ici' 3 flags bits

UCSR0B = 0x18; // bit 3-4,  rx enable, tx enable

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = 0x06;

}
  
  
// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {
	
	
while (!(UCSR0A & (1 << UDRE0))){}
UDR0 = donnee;
}

int main (void) {
	initialisationUART();
	char mots[21] = "Le robot en INF1995\n";

	uint8_t i, j;
	for ( i = 0; i < 1; i++ ) {
		for ( j=0; j < 20; j++ ) {
			
			transmissionUART ( mots[j] );
			}
		}
		//initialisationUART();
		
	
		
	return 0;	
}

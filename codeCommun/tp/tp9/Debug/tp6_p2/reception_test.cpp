
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

uint8_t USART_Receive(void){
		while (!(UCSR0A & (1 << RXC0))){}
		return UDR0;
	}

int main () {
	const uint8_t nbOctet= 22;
	initialisationUART ();
	DDRB = 0xff;
	Memoire24CXXX memoire;
	uint8_t i=0;
	uint8_t donnees[nbOctet];
	while (i<nbOctet){
		donnees[i]=USART_Receive();
		i++;
		}
	
	
	bool estpareil = true;
	const uint8_t adresseInitiale=0x00;
	memoire.ecriture(adresseInitiale,donnees, nbOctet);
	_delay_ms(15);
	uint8_t couleur =0x01;
	for (uint8_t i=0; i< nbOctet; i++){
		uint8_t temp;
	    memoire.lecture(adresseInitiale +i, &temp); //temp = out
	    couleur^=0x03;
	    PORTB= couleur;
	    _delay_ms(500);
	    if (temp != donnees[i]){
			estpareil = false;
		}		 
	}
	if (estpareil){
		PORTB =0x00;
			_delay_ms(500);
		couleur^=0x03;
			PORTB =couleur;
			_delay_ms(2000);
			}
	else
		PORTB =0x00;
	
	}


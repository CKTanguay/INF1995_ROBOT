
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

uint8_t USART_Receive(void){ // Fonction récupérant les données de l'USART 
		while (!(UCSR0A & (1 << RXC0))){}
		return UDR0;
	}

int main () {
		uint8_t i=0;
		uint8_t temp[2];
		initialisationUART ();
	while (i<2){ 	// on récupére le nbr d'instruction
		temp[i]=USART_Receive();
		i++;
		}
		uint16_t nbOctet= temp[0]; // On initialise notre la taille de notre tableau d'instructions
		nbOctet<<8;
		nbOctet +=temp[1];
		uint8_t donnees[nbOctet];
	for (int k=0; k<2; k++){ // On initialise notre tableau de données avec le nombre d'instructions
		donnees[k]=temp[k];
		}


	Memoire24CXXX memoire;
	uint8_t j=2;		
	while (j<nbOctet){		// On finit de remplir notre tableau d'instructions 
		donnees[j]=USART_Receive();
		j++;
		}
	
	const uint8_t adresseInitiale=0x00;
	memoire.ecriture(adresseInitiale,donnees, nbOctet); // on écrit notre tableau en mémoire
}
	

/* 
 * Tableau des etats:
 * Etat Entrée	Etat Suivant	Sortie
 * Init 0		Init			0
 * Init 1		E1				0
 * E1	0		E1				0
 * E1	1		E2				0
 * E2	0		E2				0
 * E2	1		E3				0
 * E3	0		E3				0
 * E3	1		E4				0
 * E4	0		E4				0
 * E4	1		E5				0
 * E5	0		Init			1
 * E5	1		Init			1
 */
#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
using namespace std;

enum Etat {Init, E1, E2, E3, E4, E5};

Etat test(Etat etatSuivant)
{
	Etat etat;
    if (PIND & 0x04){
		_delay_ms(10);
		if(~PIND & 0x04){
			etat = etatSuivant; 
		}
	}
	return etat;
}

int main()
{
  DDRA = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  DDRD = 0x00;
  PORTB = 0x00;
  Etat etat = Init;
  
  for(;;)
  {
	switch (etat){
		
		case Init: 
		etat = test(E1);
		break;
		
		case E1:
		etat = test(E2);
		break;
		
		case E2: 
		etat = test(E3);
		break;
		
		case E3: 
		etat = test(E4);
		break;
		
		case E4: 
		etat = test(E5);
		break;
		
		case E5:
		PORTB = 0x02;
		_delay_ms(1000);
		PORTB = 0x00;
		etat = test(Init);
		break;	
	}
  }
  return 0;
}


/* 
 * Tableau des etats:
 * Etat Entrée	Etat Suivant	Sortie
 * 								R	Am	V
 * 
 * Init 0		Init			1	0	0
 * Init 1		E1				1	0	0
 * E1	0		E2				0	1	0
 * E1	1		E1				0	1	0
 * E2	0		E2				0	0	1
 * E2	1		E3				0	0	1
 * E3	0		E4				1	0	0	
 * E3	1		E3				1	0	0
 * E4	0		E4				0	0	0
 * E4	1		E5				0	0	0
 * E5	0		Init			0	0	1
 * E5	1		E5				0	0	1
 */
#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
using namespace std;

enum Etat {Init, E1, E2, E3, E4, E5};

Etat test(Etat etatSuivant, Etat etat)
{
	if(etat==Init || etat==E2 || etat==E4)
	{
		if (PIND & 0x04)
		{
			_delay_ms(10);
			if(PIND & 0x04)
			{
				etat = etatSuivant; 
			}
		}
	}
	if(etat==E1 || etat==E3 || etat==E5)
	{
		if (~PIND & 0x04)
		{
			_delay_ms(10);
			if(~PIND & 0x04)
			{
				etat = etatSuivant; 
			}
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
	switch (etat)
	{
		
		case Init: 
		PORTB = 0x02;
		etat = test(E1, etat);
		break;
		
		case E1:
		while(etat != E2)
		{
		PORTB = 0x01;
        _delay_ms(6);
        PORTB = 0x02;
        _delay_ms(4);
        etat = test(E2, etat);
		}
		break;
		
		case E2: 
		PORTB = 0x01;
		etat = test(E3, etat);
		break;
		
		case E3: 
		PORTB = 0x02;
		etat = test(E4, etat);
		break;
		
		case E4: 
		PORTB = 0x00;
		etat = test(E5, etat);
		break;
		
		case E5:
		PORTB = 0x01;
		etat = test(Init, etat);
		break;	
	}
  }
  return 0;
}


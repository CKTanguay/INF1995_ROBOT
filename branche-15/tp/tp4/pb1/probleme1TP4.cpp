
#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
using namespace std;

enum Etat {Init,E1};

Etat test(Etat etatSuivant, Etat etat)
{
	if (PIND & 0x04)
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
  unsigned int compteur = 0;
  
  for(;;)
  {
	switch (etat)
	{
		
		case Init: 
		PORTB = 0x00;
		etat = test(E1, etat);
		break;
		
		case E1:
		PORTB = 0x01;
		_delay_ms(300);
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(9);
			PORTB = 0x00;
			_delay_ms(1);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(8);
			PORTB = 0x00;
			_delay_ms(2);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(7);
			PORTB = 0x00;
			_delay_ms(3);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(6);
			PORTB = 0x00;
			_delay_ms(4);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(5);
			PORTB = 0x00;
			_delay_ms(5);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(4);
			PORTB = 0x00;
			_delay_ms(6);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(3);
			PORTB = 0x00;
			_delay_ms(7);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(2);
			PORTB = 0x00;
			_delay_ms(8);
			compteur++;
		}
		compteur = 0;
		while (compteur < 30)
		{
			PORTB = 0x01;
			_delay_ms(1);
			PORTB = 0x00;
			_delay_ms(9);
			compteur++;
		}
		compteur = 0;
		Etat = E1;
		}
		break;
		
	}
  }
  return 0;
}


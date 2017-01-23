#include "Del.h"

Del::Del() : port_(B)
{}

Del::Del(TypePort& port) : port_(port)
{}

Del::~Del()
{}

void Del::modifierPort(const TypePort& port) 
{
	port_ = port;
}

void Del::allumerR() const
{
	switch (port_)
	{
		case A:
			PORTA=0x01;
			break;
		case B:
			PORTB=0x01;
			break;
		case C:
			PORTC=0x01;
			break;
		case D:
			PORTD=0x01;	
			break;
	}
}

void Del::allumerV() const
{
	switch (port_)
	{
		case A:
			PORTA=0x02;
			break;
		case B:
			PORTB=0x02;
			break;
		case C:
			PORTC=0x02;
			break;
		case D:
			PORTD=0x02;	
			break;
	}
}

void Del::allumerA() const
{
	switch (port_)
	{
		case A:
			PORTA=0x01;
			_delay_ms(2);
			PORTA=0x02;
			_delay_ms(3);
			break;
		case B:
			PORTB=0x01;
			_delay_ms(2);
			PORTB=0x02;
			_delay_ms(3);
			break;
		case C:
			PORTC=0x01;
			_delay_ms(2);
			PORTC=0x02;
			_delay_ms(3);
			break;
		case D:
			PORTD=0x01;
			_delay_ms(2);
			PORTD=0x02;
			_delay_ms(3);
			break;	
	}
}

void Del::eteindre() const
{
	switch (port_)
	{
		case A:
			PORTA=0x00;
			break;
		case B:
			PORTB=0x00;
			break;
		case C:
			PORTC=0x00;
			break;
		case D:
			PORTD=0x00;
			break;	
	}
}



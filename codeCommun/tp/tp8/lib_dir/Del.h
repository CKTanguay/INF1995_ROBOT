
#ifndef DEL_H 
#define DEL_H
#define F_CPU 8000000 
#include "TypePort.h"
#include <util/delay.h>
#include <avr/io.h>
class Del
{
	public:
		Del();
		Del(TypePort& port);
		~Del();
		void modifierPort(const TypePort& port);
		void allumerR() const;
		void allumerV() const;
		void allumerA() const;
		void eteindre() const;

	private:
		TypePort port_;
};

#endif


/* Auteur : Tom Avedissian
 * Date de création : 5/11/2016
 * Description : La classe Del permet de controler la del du robot*/

#ifndef DEL_H 
#define DEL_H
#ifndef F_CPU
#define F_CPU 8000000 
#endif
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


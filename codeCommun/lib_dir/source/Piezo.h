/* Auteurs : Tom Avedissian
 * Date de création : 25/11/2016
 * Description : La classe Piezo permet de générer un son aigu*/

#ifndef PIEZO_H
#define PIEZO_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h> 


//Puisque les méthodes sont statiquees, pas besoin de créer une instance lors de l'appel de ces fonctions
//dans un autre fichier, uniquement besoin d'inclure piezo.h

class Piezo 
{
public:
	static void jouerSonAigu(void);
	static void arreterSon(void);
	static void initialisation(void);
};
#endif

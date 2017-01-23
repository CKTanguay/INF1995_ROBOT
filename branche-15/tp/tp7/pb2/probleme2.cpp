/*
 * Fichier : probleme2.cpp
 * Auteur : Tom Avedissian
 * Date de création : 20 octobre 2016
 */
 
#define F_CPU 8000000  
#include <avr/io.h> 
#include <util/delay.h>
#include "can.cpp"


void Ambre()
{
    PORTB = 0x02;
    _delay_ms(10);
    PORTB = 0x01;
    _delay_ms(10);
}
void Lecture(uint16_t& valeurNum, can& convertisseur) // fonction qui lit et met en forme la valeur sur 16 bits retournées du convertisseur
{
    uint8_t pos = 0x01; //pos vaut 1
    valeurNum = convertisseur.lecture(pos) >> 0x02;
	valeurNum &= 0x00ff;
}


int main()
{   
  
    uint16_t valeurNum; // définition de la variable recevant les données numériques
    DDRA = 0x00; //mode entrée
    DDRB = 0xff; //mode sortie
    uint16_t luminositeForte = 200; // valeur de transition Ambre à Vert
    uint16_t luminositeFaible = 150; // valeur de transition Ambre à Rouge
    can convertisseur;
    for(;;)
    {
        Lecture(valeurNum, convertisseur);
        while(valeurNum > luminositeFaible && valeurNum < luminositeForte) // tant que luminosité moyenne
        {
            Ambre();
            Lecture(valeurNum, convertisseur);

        }
        while(valeurNum < luminositeFaible)// tant que luminosité faible
        {
            PORTB = 0x01; // vert
            Lecture(valeurNum, convertisseur);

        }
        while(valeurNum > luminositeForte)// tant que luminosité forte
        {
            PORTB = 0x02; // rouge
            Lecture(valeurNum, convertisseur);


        }
    
	}
}
	



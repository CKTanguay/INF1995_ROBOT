#ifndef FONCTION_DELAI_H
#define FONCTION_DELAI_H
//#ifndef F_CPU 
# define F_CPU 8000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>

void delai1MS(uint8_t delai);         //Delai de 1 ms

void delai5MS(uint8_t delai);         //Delai de 5 ms

void delai10MS(uint8_t delai);        //Delai de 10 ms

void delai25MS(uint8_t delai);        //Delai de 25 ms

void delai100MS(uint8_t delai);       //Delai de 100 ms -> un dixieme de seconde

void delai250MS(uint8_t delai);       //Delai de 250 ms -> un quart de seconde

void delai500MS(uint8_t delai);       //Delai de 500 ms -> une demie seconde

void delai1000MS(uint8_t delai);      //Delai de 1000 ms -> une seconde

#endif

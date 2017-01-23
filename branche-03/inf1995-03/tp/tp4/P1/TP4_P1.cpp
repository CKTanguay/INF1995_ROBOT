/****************************************************************************
* Fichier: TP4_P1.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 20 Septembre 2016
* Description: 
*
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>


 int main (){
    DDRB = 0xff;
   uint8_t tempsON =20;
   uint8_t tempsOFF=0;
   uint8_t compteur = 0;
   for (;;){
       PORTB = 0x01;
       for (uint8_t i=0; i < tempsON; i++)
           _delay_ms(1);
       PORTB = 0x00;
       for (uint8_t i=0; i<tempsOFF; i++)
           _delay_ms(1);
       if (compteur == 7){
           compteur =0;
           tempsON --;
           tempsOFF ++;
        }
        if (tempsON ==0 || tempsOFF ==20){
            tempsON =20;
           tempsOFF=0;
        }
        compteur ++;
    }
     
}

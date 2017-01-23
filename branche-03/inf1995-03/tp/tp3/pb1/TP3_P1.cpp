/****************************************************************************
* Fichier: TP3_P1.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 20 Septembre 2016
* Description: Ce programme fait en sorte qu'après avoir appuyé 5 fois sur le bouton, une DEL s'allume pendant une seconde.
*
* État courant     #        compteur      # Couleur de sortie 
* État Initial     #           0          # Aucune couleur
* DEL Allumée      #           5          # Rouge (pendant une seconde)
****************************************************************************/


#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>

bool risingEdge(bool lastState, bool currentState)
{
    if(lastState != currentState && currentState ==true)
    {
        _delay_ms(10);
        if (lastState != currentState && currentState ==true)
        {
            return true;
        }
    }
    
    return false;
}

bool fallingEdge(bool lastState, bool currentState)
{
    if(lastState != currentState && currentState == false)
    {
        _delay_ms(10);
        if (lastState != currentState && currentState == false)
        {
            return true;
        }
    }
    
    return false;
}

int main()
{
   DDRB = 0xff;      
   DDRD = 0x00;      
   PORTB = 0x00;
   bool lastState = (PIND & 0x04);
   bool currentState = (PIND & 0x04);
   uint8_t nbOccurencesBP=0;
   for(;;){
        currentState =(PIND & 0x04);
        if(fallingEdge(lastState, currentState)){
                nbOccurencesBP++;
                lastState = currentState;
            }
        else if (risingEdge(lastState, currentState)){
                 lastState = currentState;
             }
        if (nbOccurencesBP == 5){
            PORTB =0x01;
            _delay_ms(1000);
            PORTB =0x00;
            nbOccurencesBP=0;
        }
   }
return 0;
}




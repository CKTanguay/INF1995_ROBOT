/****************************************************************************
 * Fichier: TP3_P2.cpp
 * Auteurs: Maxime Brousseau 1828528
 *          Christophe Kedzierski-Tanguay 1827066
 * Date de dernière modification: 20 Septembre 2016
 * Ce programme fait alterner les couleurs de la led selon un certain ordre. 
 * 
 * État courant     #         Entrée bouton-poussoir       # Couleur de sortie (de l'état courant)
 *                  #        0          #        1         #        
 * etatInitial      #  etatInitial      # ambre            # Couleur rouge
 * ambre            #  vertInactif      # ambre            # Couleur ambre
 * vertInactif      #  vertInactif      # rougeActif       # Couleur verte
 * rougeActif       #  ledEteinte       # rougeActif       # Couleur rouge
 * ledEteinte       #  ledEteinte       # vertActif        # Aucune couleur
 * vertActif        #  etatInitial      # vertActif        # Couleur verte
 ****************************************************************************/


#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>

bool pressBtn(){
    if(PIND & 0x04)
    {
        _delay_ms(10);
        if(PIND & 0x04)
            return true;
    }    
    
    return false;
}

enum State {etatInitial, ambre, vertInactif, rougeActif, ledEteinte, vertActif};

int main(){
    
    DDRB = 0xff;      // xxxxyyyy
    DDRD = 0x00;      // 87654321
    int currentState=0;
    
    for(;;){
        
        switch(currentState)
        {
        
            case etatInitial:
            {
                PORTB=0x01;
                if(pressBtn())
                    currentState=ambre;
                break;
            }
            
            case ambre:
            {
                int compteur=0;
                while(PIND & 0x04){
                    compteur++;
                    if (compteur %6 == 0)
                        PORTB = 0x01;
                    else PORTB = 0x02;
                }
                currentState=vertInactif;
                break;                
            }
            
            case vertInactif:
            {
                PORTB=0x02;
                if(pressBtn())
                    currentState=rougeActif;
                break;
            }
            
            case rougeActif:
            {
                while(pressBtn())
                    PORTB=0x01;
                currentState=ledEteinte;                
                break;
            }
            
            case ledEteinte:
            {
                PORTB=0x00;
                if(pressBtn())
                    currentState=vertActif;
                break;
            }
            
            case vertActif:
            {
                while(pressBtn())
                    PORTB=0x02;
                currentState=etatInitial;
                break;
            }
        }
    }
    return 0;
}
    

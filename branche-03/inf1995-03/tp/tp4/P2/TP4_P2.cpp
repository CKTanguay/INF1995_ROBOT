/****************************************************************************
* Fichier: TP4_P2.cpp
* Auteurs: Maxime Brousseau 1828528
*          Christophe Kedzierski-Tanguay 1827066
* Date de dernière modification: 23 Septembre 2016
* Description: 
*
*/

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>


 int main ()
{    
    int compteurDelai1Eteint;
    int compteurDelaiAllume;
    int compteur;
     
	DDRB = 0xff;
    
//###########---60Hz---#######################    
    
    //moteur a 0%
	compteur=0;
	compteurDelai1Eteint=33333;
	compteurDelaiAllume=0;
	
	while(compteur<120)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
				
		compteur++;		
	}
	
	//moteur a 25%
	compteur=0;
	compteurDelai1Eteint=25000;
	compteurDelaiAllume=8333;
	
	while(compteur<120)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	//moteur a 50%
	compteur=0;
	compteurDelai1Eteint=16666;
	compteurDelaiAllume=16666;
	
	while(compteur<120)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}	
				
	//moteur a 75%
	compteur=0;
	compteurDelai1Eteint=25000;
	compteurDelaiAllume=8333;
	
	while(compteur<120)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	//moteur a 100%
	compteur=0;
	compteurDelai1Eteint=0;
	compteurDelaiAllume=33333;
	
	while(compteur<120)
	{		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	PORTB=0x00;
		
//#################---400Hz---###############################
          
    //moteur a 0%
	compteur=0;
	compteurDelai1Eteint=20000;
	compteurDelaiAllume=0;
	
	while(compteur<200)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
				
		compteur++;		
	}
	
	//moteur a 25%
	compteur=0;
	compteurDelai1Eteint=15000;
	compteurDelaiAllume=5000;
	
	while(compteur<200)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	//moteur a 50%
	compteur=0;
	compteurDelai1Eteint=10000;
	compteurDelaiAllume=10000;
	
	while(compteur<200)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}	
				
	//moteur a 75%
	compteur=0;
	compteurDelai1Eteint=5000;
	compteurDelaiAllume=15000;
	
	while(compteur<200)
	{
		PORTB=0x00;
		_delay_loop_2(compteurDelai1Eteint);
		
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	//moteur a 100%
	compteur=0;
	compteurDelai1Eteint=0;
	compteurDelaiAllume=20000;
	
	while(compteur<200)
	{	
		PORTB=0x01;
		_delay_loop_2(compteurDelaiAllume);
		
		compteur++;		
	}
	
	PORTB=0x00;
   
}


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

void clignoter100ms(){
    for ( int i = 0; i < 5; i++){
        PORTA = 0x02; 
        _delay_ms(20.0);
        PORTA = 0x00;
        
    }
}

ISR (TIMER1_COMPA_vect) {
    
    minuterieExpiree = 1;
    
}


ISR (INT0_vect) {
    
    boutonPoussoir = 1;
    
    // anti-rebond
    _delay_ms(30);
    if ( PIND & 0x04 ){ //bouton pressé
        boutonPoussoir = 1;
    }
    
}

void partirMinuterie ( uint16_t duree ) {
    
    minuterieExpiree = 0;
    
    // mode CTC du timer 1 avec horloge divisee par 1024
    
    // interruption apres la duree specifiee
    
    TCNT1 = 0 ;
    
    OCR1A = duree;

    //ICI VOIR SECTION 16.12 doc Atmel
    
    TCCR1A = 0x0C;//C = mode CTC
    
    TCCR1B = 0x05;//prescaler 1024 [ CSn2 et CSn0 à 1 == clkI/O/1024 (From prescaler)]
    
    TCCR1C = 0;
    
    TIMSK1 = 0x02; //TIMER1_COMPA_vect
    
}

void initialisation ( void ) {
    
    // cli est une routine qui bloque toutes les interruptions.
    
    // Il serait bien mauvais d'etre interrompu alors que
    
    // le microcontroleur n'est pas pret...
    
    cli ();
    
    // configurer et choisir les ports pour les entrees
    
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree (bouton poussoir)
    
    // cette procédure ajuste le registre EIMSK
    
    // de ATmega324PA pour permettre les interruptions externes
    
    EIMSK |= _BV(INT0);
    
    // il faut sensibiliser les interruptions externes aux
    
    // changements de niveau du bouton-poussoir
    
    // en ajustant le registre EICRA
    
    EICRA |= 0x01;
    
    // sei permet de recevoir a nouveau des interruptions.
    
    sei ();
    
}

int main()
{
    initialisation();
    //attendre 10 secondes
    for (int i = 0; i < 100; i ++){
        _delay_ms(100);
    }
    
    clignoter100ms();
    boutonPoussoir = 0; //Permet de ne pas tricher (en pesant sur le bouton avant la fin du clignotement)
    PORTA = ETEINT;
    
    partirMinuterie(7813); //8MHz / 1024 = 7812.5 cycles (1 seconde)
    do {
        
        // attendre qu'une des deux variables soit modifiee
        
        // par une ou l'autre des interruptions.
        
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
    
    
    // Une interruption s'est produite. Arreter toute
    
    // forme d'interruption. Une seule reponse suffit.
    
    cli ();
    
    // Verifier la reponse
    
    if (minuterieExpiree == 1){
        PORTA = ROUGE;
    }else{
        PORTA = VERT;
    }
    
}



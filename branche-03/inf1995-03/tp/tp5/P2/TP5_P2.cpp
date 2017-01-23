#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;  	
ISR (TIMER1_COMPA_vect) {
minuterieExpiree = 1;
}

ISR (INT0_vect) {
_delay_ms(30);
boutonPoussoir = 1;
// boutonPoussoir==1;
EIFR |= (1 << INTF0); 
}

void initialisation ( void ) {

	cli ();
	DDRB = 0xff;   
    DDRD = 0x00;      
	EIMSK |= _BV(INT0);
	EICRA |= _BV(ISC00);
	sei ();
	PORTB=0x00;

}

void partirMinuterie ( uint16_t duree ) {
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0x04; 
	TCCR1B = 0x05; 
	TCCR1C = 0; 
	TIMSK1 = _BV(OCIE1A); // (1 << OCIE1A) equivalant
}


 int main(){
	 
	 
	 initialisation();
	 _delay_ms(3000);
	 PORTB=0x01;
	 _delay_ms(100);
	 PORTB=0x00;
	 partirMinuterie(0x1E84>>1); 
		
	do {	
	} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
	
	cli ();
	
	if(boutonPoussoir==1) 
		PORTB=0x02;
		
	else 
		PORTB=0x01;	
		
	return 0;
 }

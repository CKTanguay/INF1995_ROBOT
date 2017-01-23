#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t m=0x01;
volatile uint8_t boutonPoussoir;


ISR (TIMER0_COMPA_vect) {
PORTB^=0x03;
	

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




 int main(){
	initialisation();
	PORTB=0x02;
	_delay_ms(1000);
	TCNT0 = 0; 
	OCR0A = 122;
	TCCR0A = 0x01;
	TCCR0B = 0x03; 
	TIMSK0 = _BV(OCIE0A);
	 while (1){
		
	}
	return 0;
 }

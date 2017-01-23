#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){
	DDRD = 0x00;
	for (;;){
		PORTD=0xff;
		}
return 0;
	}

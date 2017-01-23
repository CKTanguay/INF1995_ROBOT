#include "pwm.h"
void pwm60Hz (uint16_t poucentage){
switch(poucentage){
    case 0:
        PORTB=0x00;
		_delay_loop_2(33333);
        break;
    case 25:
        	PORTB=0x00;
		_delay_loop_2(25000);
		
		PORTB=0x01;
		_delay_loop_2(8333);
        break;
    case 50:
        	PORTB=0x00;
		_delay_loop_2(16666);
		
		PORTB=0x01;
		_delay_loop_2(16666);
        break;
    case 75:
        	PORTB=0x00;
		_delay_loop_2(8333);
		
		PORTB=0x01;
		_delay_loop_2(25000);
        break;
    case 100:
         PORTB=0x01;
		_delay_loop_2(33333);
        break;


    }
}
void pwm400Hz (uint16_t poucentage){
switch(poucentage){
    case 0:
        PORTB=0x00;
		_delay_loop_2(20000);
        break;
    case 25:
        	PORTB=0x00;
		_delay_loop_2(15000);
		
		PORTB=0x01;
		_delay_loop_2(5000);
        break;
    case 50:
        	PORTB=0x00;
		_delay_loop_2(10000);
		
		PORTB=0x01;
		_delay_loop_2(10000);
        break;
    case 75:
        	PORTB=0x00;
		_delay_loop_2(5000);
		
		PORTB=0x01;
		_delay_loop_2(15000);
        break;
    case 100:
         PORTB=0x01;
		_delay_loop_2(20000);
        break;


    }
}

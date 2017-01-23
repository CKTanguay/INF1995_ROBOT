
#ifndef F_CPU
/* fournir un avertissement mais non une erreur */
# warning "F_CPU pas defini pour 'memoire_24.cpp'"
# define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
void pwm60Hz (uint16_t poucentage);
void pwm400Hz (uint16_t poucentage);


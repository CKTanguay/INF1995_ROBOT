#ifndef BOUTON_POUSSOIR_H
#define BOUTON_POUSSOIR_H

#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>

#include "TypePort.h"

class BoutonPoussoir
{
public:
    BoutonPoussoir();
    ~BoutonPoussoir();
    bool antiRebond(const TypePort& port);

private:
    bool etat_;

};

#endif

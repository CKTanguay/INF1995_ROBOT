#include <avr/io.h>
#include <stdint.h>
#include "Robot.h"
#include "Del.h"
#include "FonctionDelai.h"
#include "Piezo.h"



int main ()
{	
	
	Robot robot(40);
	Del del;
	Piezo::initialisation();
	

Piezo::arreterSon();
	for(;;)
	{
		char foo = robot.identifierCouleur(1);
	}
	return 0;
}

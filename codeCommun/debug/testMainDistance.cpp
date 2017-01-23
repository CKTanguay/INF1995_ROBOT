#include <avr/io.h>
#include <stdint.h>
#include "Robot.h"

// valeurs de reception des capteurs
#define capteur1 0x02
#define capteur2 0x01
#define capteur3 0x08
#define capteur4 0x04
#define capteur5 0x20

//combinaison des capteurs

#define capteurs1_2 0x03
#define capteurs3_2_1 0x0B
#define capteurs1_2_3_4 0x0D
#define capteurs3_2 0x05
#define capteurs3_4 0x0C
#define capteurs4_5 0x24
#define capteurs3_4_5 0x2C
#define capteurs2_3_4_5 0x2D
#define capteurs1_2_3_4_5 0x2F

/*Pour le parcours demandé, on sait que le robot aura à tourner 5 fois sur la droite, 1 fois sur la gauche et ne plus tourner.*/ 
//largeur salle=60cm (60.5)
//distance entre capteur de distance et point de pivot du robot =11.5

int main ()
{	
	
	Robot robot(55);
	robot.avancer();
	bool foo =true;
	while(foo)
	{
		robot.lireBitsCapteur();
		
			if(robot.obstacleEstProche())
			{
				foo=false;
			}
	
		}
		robot.arreter();
				char foo1 = robot.identifierPiece();
}


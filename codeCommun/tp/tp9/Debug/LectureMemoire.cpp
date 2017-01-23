#include "LectureMemoire.h"

LectureMemoire::LectureMemoire()
{
	adresseInitiale_ = 0x00;
	longueurLecture_ = sizeof(uint8_t);
	adresseLongueurBCode_ = 0x02; //Deuxieme octet du bytecode
}

//~LectureMemoire(){}

dataMem LectureMemoire::getPtrData() const
{
	return ptrData_;
}

dataMem LectureMemoire::lectureContenu() 
{
	Memoire24CXXX mem24;
	
	uint8_t i=0;
			
	while(!(0xFF))	//while not end of file
	{
		mem24.lecture(adresseInitiale_ + i++, &ptrData_.oper, longueurLecture_);	/////////
		mem24.lecture(adresseInitiale_ + i++, &ptrData_.operande, longueurLecture_);	/////////
		//storage des donnees si on en a besoin potentiellement
	}
	return ptrData_;
}

//le mrrobot.o est pas créé car il faut un main ici tout simplement (juste un return0 dans main)


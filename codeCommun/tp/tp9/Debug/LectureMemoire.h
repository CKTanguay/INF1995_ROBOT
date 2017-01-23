#ifndef LECTURE_MEMOIRE_H
#define LECTURE_MEMOIRE_H

#include "memoire_24.h"

typedef struct
{
	uint8_t oper;
	uint8_t operande;
} dataMem;

class LectureMemoire
{
public:
	LectureMemoire();
	//~LectureMemoire();
	
	dataMem lectureContenu();
	
	dataMem getPtrData() const;
	
private:
	dataMem ptrData_ ;
	uint16_t adresseInitiale_ = 0x00;
	uint8_t longueurLecture_ = sizeof(uint8_t);
	uint16_t adresseLongueurBCode_ = 0x02; //Deuxieme octet du bytecode
};

#endif

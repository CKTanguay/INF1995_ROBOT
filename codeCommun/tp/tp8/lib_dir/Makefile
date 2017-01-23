########       AVR Project Makefile   	  ########
#####                                        #####
#####	   Makefile produit et ecrit par     #####
#####	equipe 0315			     #####
#####		 INF1995 - 2016		     #####
#####					     #####
#####	      Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################
## makefile library
# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++


#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom de la librairie généré
LIBNAME=robot

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=mrRobot

# Fichiers sources
# (Listez tous les fichiers a compiler, ex: 'tp1.c, tp2.cpp'):
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC=*.cpp
# Inclusions additionnels (ex: -I/path/to/mydir)
INC=
 

# Libraires a lier (ex: -lmylib)
LIBS= 
# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp



####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de ##### 
#####   ce Makefile en vue de sa modification  #####
####################################################



####### variables #######

#compilateur utilise
CC=avr-gcc
#compilateur librairies
CL= avr-ar
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex



####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall                                        

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)



####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex



####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
	
# Pour plus d'information sur cette section, consulter :
# http://bit.ly/257R53E	
# Les fonctions $(filter pattern…,text) &
# $(patsubst pattern,replacement,text) sont pertinentes
	


####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make delete et make clean
.PHONY: all clean delete lib

# Make all permet simplement de compiler le projet
#
all: *.cpp
	$(CC) -Os -mmcu=$(MCU) -c *.cpp 
	$(CL) crs lib$(LIBNAME).a *.o 
	$(REMOVE) $(OBJDEPS) *.d 
	

clean:
	$(REMOVE) $(OBJDEPS) *.d 
delete: 
	$(REMOVE) $(OBJDEPS) *.d lib$(LIBNAME).a



# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####

#Makefile de Test

# Fonction utilise dans ce makefile :
# filter-out permet de prendre tout sauf certaine chaine de caractere d'une liste
# subst remplace une chaine de caractere par une autre


PROG = OUTILS_SDL_test
#Nom du fichier .c et .h du test
NOM_TEST=test_outils_sdl

CFLAGS = -Wall -g
RACINE=../../

CC = gcc

#----------------------------------------------------------------------------------
# INCLUDE SDL2
#----------------------------------------------------------------------------------

SDL_DIR=$(HOME)/SDL2
SDLLIB_DIR=$(SDL_DIR)/lib
SDLINC_DIR=$(SDL_DIR)/include
LIBS=-L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I$(SDLINC_DIR)

#----------------------------------------------------------------------------------
# Repertoire
#----------------------------------------------------------------------------------
OBJ_DIR=$(RACINE)obj
SRC_DIR=$(RACINE)src
BIN_DIR=$(RACINE)bin
INC_DIR=$(RACINE)include
TEST_DIR=

# Toutes les sources du projet
ALL_SRC = $(wildcard $(SRC_DIR)/*.c)
ALL_INC = $(wildcard $(INC_DIR)/*.h)

SRC = $(filter-out $(SRC_DIR)/world_of_dungeons.c,$(ALL_SRC))
INC = $(filter-out $(INC_DIR)/world_of_dungeons.h,$(ALL_INC))

OBJ := $(subst .c,.o,$(SRC))
OBJ := $(subst src,obj,$(OBJ))

#---------------------------------------------------------------------------------
# Création des fichier de stockage des binaires et objets s'il n'existe pas
#--------------------------------------------------------------------------------

DIRS = $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)


all: $(DIRS) $(BIN_DIR)/$(PROG)
		@echo -e '\033[42m Makefile Test : $(NOM_TEST) \033[0m'

$(BIN_DIR)/$(PROG): $(OBJ) $(NOM_TEST).o
	@echo Compilation de $@ grace a $^
	$(CC) $(CFLAGS) $^ -o $@  $(LIBS) $(INCLUDES) -I$(INC_DIR)

$(NOM_TEST).o: $(NOM_TEST).c $(NOM_TEST).h
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I$(INC_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@echo Compilation de $@ grace a $^
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I$(INC_DIR)

#-----------------------------------------------------------------------------------
# Regle pour effacer tous les objets et binaires
#------------------------------------------------------------------------------------

.PHONY: clean mrproper

clean:
	rm $(OBJ_DIR)/*.o
	rm *.o

mrproper: clean
	rm -i $(BIN_DIR)/$(PROG)

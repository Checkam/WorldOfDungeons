#Les tests ne peuvent pas être make dans la racine du projet
#Un fichier est dédié pour les tests (test)
#Ceci est le makefile de test
PROG = MENU_test
#Nom du fichier .c et .h du test
NOM_TEST=test_menu

CFLAGS = -Wall -g
RACINE=../../

CC = gcc

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

ALL_SRC = $(wildcard $(SRC_DIR)/*.c)
ALL_INC = $(wildcard $(INC_DIR)/*.h)

 # Wildcard fonction qui récupère tous les fichiers

SRC = $(filter-out $(SRC_DIR)/world_of_dungeons.c,$(ALL_SRC))
INC = $(filter-out $(INC_DIR)/world_of_dungeons.h,$(ALL_INC))

OBJ := $(subst .c,.o,$(SRC))
OBJ := $(subst src,obj,$(OBJ))

DIRS = $(OBJ_DIR) $(BIN_DIR)

all: $(DIRS) $(BIN_DIR)/$(PROG)
		@echo -e '\033[42m Makefile Test : $(NOM_TEST) \033[0m'

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

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

#Makefile de Test

# Fonction utilise dans ce makefile :
# filter-out permet de prendre tout sauf certaine chaine de caractere d'une liste
# subst remplace une chaine de caractere par une autre


PROG = MAP_test
#Nom du fichier .c et .h du test
NOM_TEST=test_map

RACINE=../../

include $(RACINE)Makefile.conf

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

#----------------------------------------------------------------------------------
# Messages
#----------------------------------------------------------------------------------
MSG_CC = @echo "  CC    " $@;
MSG_RM_O = @echo "  RM    " *.o;
MSG_RM_B = @echo "  RM    " $(BIN_DIR)/$(PROG);

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


ifeq ($(MESSAGE), yes)
all: DEB_CC $(DIRS) $(BIN_DIR)/$(PROG) FIN_CC
else
all: $(DIRS) $(BIN_DIR)/$(PROG)
endif

DEB_CC:
	@echo -e '\033[42m Début Compilation : $(NOM_TEST) \033[0m'
FIN_CC:
	@echo -e '\033[42m Fin Compilation : $(NOM_TEST) \033[0m'

$(BIN_DIR)/$(PROG): $(OBJ) $(NOM_TEST).o
	$(MSG_CC)$(CC) $(CFLAGS) $^ -o $@  $(LIBS) $(INCLUDES) -I$(INC_DIR)

$(NOM_TEST).o: $(NOM_TEST).c $(NOM_TEST).h
	$(MSG_CC)$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I$(INC_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(MSG_CC)$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I$(INC_DIR)

#-----------------------------------------------------------------------------------
# Regle pour effacer tous les objets et binaires
#------------------------------------------------------------------------------------

.PHONY: clean mrproper

clean:
	$(MSG_RM_O)rm -f *.o

mrproper: clean
	$(MSG_RM_B)rm -i $(BIN_DIR)/$(PROG)

#Makefile principal

# Fonction utilise dans ce makefile :
# wildcard fonction qui récupère tous les fichiers
# foreach un for utilisable comme ceci $(foreach i,$(liste),commande $(i);)

include Makefile.conf

CC = gcc
PROG = world_of_dungeons
MAKE=/usr/bin/make

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
OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
INC_DIR=include
TEST_DIRS=$(wildcard test/*)

# Toutes les sources du projet
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#----------------------------------------------------------------------------------
# Messages
#----------------------------------------------------------------------------------
MSG_CC = @echo "  CC    " $@;
MSG_CC_TEST_DEB = @echo '\033[42m Début Compilation : TEST \033[0m';
MSG_CC_TEST_FIN = @echo '\033[42m Fin Compilation : TEST \033[0m';
MSG_RM_O = @echo "  RM    " $(OBJ_DIR)/*.o;
MSG_RM_B = @echo "  RM    " $(BIN_DIR)/*;
MSG_RM_P = @echo "  RM    " $(BIN_DIR)/$(PROG);
MSG_RM_TEST_O_DEB = @echo '\033[42m Début Suppression : OBJET TEST\033[0m';
MSG_RM_TEST_O_FIN = @echo -e '\033[42m Fin Suppression : OBJET TEST\033[0m'

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
	@echo -e '\033[42m Début Compilation : $(PROG) \033[0m'
FIN_CC:
	@echo -e '\033[42m Fin Compilation : $(PROG) \033[0m'

$(BIN_DIR)/$(PROG): $(OBJ)
	$(MSG_CC)$(CC) $^ -o $@  $(LIBS) $(INCLUDES) -I./$(INC_DIR) $(CFLAGS)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(MSG_CC)$(CC) -o $@ -c $< $(LIBS) $(INCLUDES) -I./$(INC_DIR) $(CFLAGS)

#PHONY oblige l'execution même si les dependences n'ont pas change (Obligatoire pour test sinon il ne s execute pas forcement)

.PHONY: clean mrproper help test

#-----------------------------------------------------------------------------------
# Regle pour effacer tous les objets et binaires
#------------------------------------------------------------------------------------


clean:
	$(MSG_RM_O)rm -f $(OBJ_DIR)/*.o
	$(MSG_RM_B)rm -f $(BIN_DIR)/*
	$(MSG_RM_TEST_O_DEB)$(foreach i,$(TEST_DIRS),$(MAKE) -s -C $(i) clean;)
	$(MSG_RM_TEST_O_FIN)

mrproper: clean
	$(MSG_RM_P)rm -i $(BIN_DIR)/$(PROG)

#-----------------------------------------------------------------------------------
# Autre regle
#------------------------------------------------------------------------------------


help:
	@echo
	@echo 'Option disponible'
	@echo '-------------------------------------------------------------------------------------------'
	@echo '- all'
	@echo '- test'
	@echo '- clean'
	@echo '- mrproper'
	@echo '-------------------------------------------------------------------------------------------'

test:
	$(MSG_CC_TEST_DEB)$(foreach i,$(TEST_DIRS),$(MAKE) -s -C $(i) all;)
	$(MSG_CC_TEST_FIN)

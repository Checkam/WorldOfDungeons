#Makefile principal

# Fonction utilise dans ce makefile :
# wildcard fonction qui récupère tous les fichiers
# foreach un for utilisable comme ceci $(foreach i,$(liste),commande $(i);)

CC = gcc
CFLAGS = -Wall -g
PROG = gen_map
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

#---------------------------------------------------------------------------------
# Création des fichier de stockage des binaires et objets s'il n'existe pas
#--------------------------------------------------------------------------------

DIRS = $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(DIRS) $(BIN_DIR)/$(PROG)
	@echo -e '\033[42m Makefile du programme principal: $(PROG) \033[0m'

$(BIN_DIR)/$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@  $(LIBS) $(INCLUDES) -I./$(INC_DIR)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I./$(INC_DIR)

#PHONY oblige l'execution même si les dependences n'ont pas change (Obligatoire pour test sinon il ne s execute pas forcement)

.PHONY: clean mrproper help test

#-----------------------------------------------------------------------------------
# Regle pour effacer tous les objets et binaires
#------------------------------------------------------------------------------------


clean:
	rm $(OBJ_DIR)/*.o
	rm $(BIN_DIR)/*

mrproper: clean
	rm -i $(BIN_DIR)/$(PROG)

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
	$(foreach i,$(TEST_DIRS),$(MAKE) -C $(i) all;)

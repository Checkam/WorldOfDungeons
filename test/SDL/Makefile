#Les tests ne peuvent pas être make dans la racine du projet
#Un fichier est dédié pour les tests (test)
#Ceci est le makefile de test
PROG = World_Of_Dungeons_test
CFLAGS = -Wall -g
RACINE=../../
CUR_DIR=./


CC = gcc

SDL_DIR=$(HOME)/SDL2
SDLLIB_DIR=$(SDL_DIR)/lib
SDLINC_DIR=$(SDL_DIR)/include

LIBS=-L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I$(SDLINC_DIR)

OBJ_DIR=$(RACINE)obj
SRC_DIR=$(RACINE)src
BIN_DIR=$(RACINE)bin
INC_DIR=$(RACINE)include
TEST_DIR=./

ALL_SRC = $(wildcard $(SRC_DIR)/*.c)
ALL_INC = $(wildcard $(INC_DIR)/*.h)

 # Wildcard fonction qui récupère tous les fichiers

SRC = $(filter-out $(RACINE)world_of_dungeons.c,$(ALL_SRC))
INC = $(filter-out $(RACINE)world_of_dungeons.h,$(ALL_INC))


SRC += $(wildcard $(TEST_DIR)/*.c)
INC += $(wildcard $(TEST_DIR)/*.h)

.PHONY: affichage

affichage:
	@echo $(SRC)

 # On crée la liste des OBJ grâce aux .c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIRS = $(OBJ_DIR) $(BIN_DIR)

all: $(DIRS) $(BIN_DIR)/$(PROG)
		@echo Makefile Test : $(TEST)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@  $(LIBS) $(INCLUDES) -I$(INC_DIR)


$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I$(INC_DIR)

.PHONY: clean mrproper

clean:
	rm $(OBJ_DIR)/*.o
	rm $(BIN_DIR)/*

mrproper: clean
	rm -i $(BIN_DIR)/$(PROG)

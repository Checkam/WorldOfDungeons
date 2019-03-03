CC = gcc
CFLAGS = -Wall -g
PROG = gen_map

SDL_DIR=$(HOME)/SDL2
SDLLIB_DIR=$(SDL_DIR)/lib
SDLINC_DIR=$(SDL_DIR)/include

LIBS=-L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I$(SDLINC_DIR)

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
INC_DIR=include

SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DIRS = $(OBJ_DIR) $(BIN_DIR)

all: $(DIRS) $(BIN_DIR)/$(PROG)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@  $(LIBS) $(INCLUDES) -I./$(INC_DIR)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(INCLUDES) -I./$(INC_DIR)

clean:
	rm $(OBJ_DIR)/*.o
	rm *.gch

mrproper: clean
	rm -i $(BIN_DIR)/$(PROG)

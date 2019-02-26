CC = gcc
CFLAGS = -Wall
PROG = gen_map
OBJ = gen_map.o seed.o liste.o procedural.o

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 


all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@  ${LIBS} ${INCLUDES} -I./

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^ ${LIBS} ${INCLUDES} -I./
	
clean:
	rm *.o

mrproper: clean
	rm -i $(PROG)
CC = gcc
CFLAGS = -Wall -g
PROG = test_json
OBJ = test_json.o json.o

all : $(PROG)

$(PROG) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(CFLAGS)

test_json.o : test_json.c ../../include/json.h
	$(CC) -c $< $(CFLAGS)

json.o : ../../src/json.c ../../include/json.h
	$(CC) -c $< $(CFLAGS)
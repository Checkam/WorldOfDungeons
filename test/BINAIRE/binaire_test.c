#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <erreur.h>
#include <binaire.h>
#include <assert.h>

int main(int argc, char **argv, char ** env) {
    printf("-------- Programme de Test du Module BINAIRE --------\n");

    pwd_init(argv[0],getenv("PWD"));
    
    pwd_quit();
    return OK;
}

#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <erreur.h>
#include <binaire.h>
#include <assert.h>
#include <memory.h>
#include "binaire_test.h"

int main(int argc, char **argv, char ** env) {
    printf("-------- Programme de Test du Module BINAIRE --------\n");

    pwd_init(argv[0],getenv("PWD"));
    printf("%d\n",add(1,2));
    pwd_quit();
    return OK;
}

static int add (int a, int b)
{
    return a + b;
}

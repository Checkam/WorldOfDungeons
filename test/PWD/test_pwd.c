/**
 * \file test_pwd.c
 * \brief Programme qui teste que le module pwd.
 * \author GALBRUN Tibane
 * \date 09/03/2019
 * \version 0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <chemin.h>
#include <assert.h>
#include "test_pwd.h"

int main(int argc, char ** argv, char ** env)
{
    printf("----- Programme de Test de Récupération du PWD de WoD -----\n");

    printf("Création de WOD_PWD :\n");
    assert(pwd_init(argv[0], getenv("PWD")) == OK);
    printf("\t-- OK\n");

    printf("WOD_PWD = %s\n", WOD_PWD);

    printf("Création d'un chemin vers de le dossier 'test/PWD/'\n");
    char * chemin;
    creation_chemin("test/PWD/",&chemin);
    printf("\t-- OK\n");
    printf("Chemin = %s\n", chemin);

    pwd_quit();
    free(chemin);

    return EXIT_SUCCESS;
}
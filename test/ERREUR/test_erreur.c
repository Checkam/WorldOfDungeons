/**
 * \file test_erreur.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Tibane.
 * \date 07/03/2019
 * \version 0.1
*/

#include <erreur.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <chemin.h>

int main(int argc, char ** argv, char ** env)
{
    getpwd(argv[0], getenv("PWD"));

    /* Test de toutes les erreurs */
    int i;
    for(i = 0; i < NB_ERREUR; i++){
        printf("Test Erreur %d\n", i);
        assert(aff_erreur(i, NULL) == OK);
        printf("\t-- OK\n");
    }

    free(WOD_PWD);
    return EXIT_SUCCESS;
}
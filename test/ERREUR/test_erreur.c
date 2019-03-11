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

    /* Test de l'affichage de toutes les erreurs */
    printf("Test affichage de toutes les erreurs\n");
    int i;
    for(i = 0; i < NB_ERREUR; i++){
        assert(erreur_afficher(i, NULL) == OK);
    }
    printf("\t--OK\n");

    /* Test affichage erreur PTR_NULL + msg */
    printf("\nTest affichage erreur PTR_NULL + message en plus\n");
    assert(erreur_afficher(PTR_NULL, "menu_creer() - pointeur sur le menu") == OK);
    printf("\t--OK\n");

    /* Test de l'enregistrement de toutes les erreurs */
    printf("\nTest enregistrement de toutes les erreurs\n");
    for(i = 0; i < NB_ERREUR; i++){
        assert(erreur_save(i, NULL) == OK);
    }
    printf("\t--OK\n");

    /* Test enregistrement erreur PTR_NULL + msg */
    printf("\nTest enregistrement erreur PTR_NULL + message en plus\n");
    assert(erreur_save(PTR_NULL, "menu_creer() - pointeur sur le menu") == OK);
    printf("\t--OK\n");

    free(WOD_PWD);
    return EXIT_SUCCESS;
}
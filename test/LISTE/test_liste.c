/**
 * \file test_liste.c
 * \brief Programme qui teste que le module liste.
 * \author GALBRUN Tibane
 * \date 07/03/2019
 * \version 0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <liste.h>
#include "test_liste.h"

int main()
{
    printf("----- Programme de Test de Liste Générique -----\n");

    /* Valeurs */
    float * a = malloc(sizeof(float)); *a = 1.1;
    float * b = malloc(sizeof(float)); *b = 2.2;
    float * c = malloc(sizeof(float)); *c = 3.3;

    /* Déclaration des listes */
    t_liste j1;

    /* Création des listes */
    printf("\t--> Création de la Liste Générique\n");
    init_liste(&j1);
    printf("\t\t-- OK\n");

    /* Remplissage des listes avec des valeurs quelconques */
    printf("\t--> Remplissage de la Liste Générique\n");
    en_tete(&j1);
    ajout_droit(&j1,a);
    ajout_droit(&j1,b);
    ajout_droit(&j1,c);
    printf("\t\t-- OK\n");

    /* Affichage des listes */
    printf("\t--> Affichage de la Liste Générique\n");
    afficher_liste(&j1);
    printf("\t\t-- OK\n");

    /* Destruction des listes */
    printf("\t--> Destruction des Listes\n");
    detruire_liste(&j1);
    printf("\t\t-- OK\n");

    return EXIT_SUCCESS;
}

void afficher_liste(t_liste * p)
{
    for(en_tete(p);!hors_liste(p);suivant(p))
    {
        float * val;
        valeur_elt(p,(void **)&val,sizeof(float *));
        printf("%.2f ", *val);
    }
    printf("\n");
}
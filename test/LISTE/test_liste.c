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
    int a = 1;

    /* Déclaration des listes */
    t_liste j1;

    /* Création des listes */
    printf("\t--> Création de la Liste Générique\n");
    init_liste(&j1);
    printf("\t\t-- OK\n");

    /* Remplissage des listes avec des valeurs quelconques */
    printf("\t--> Remplissage de la Liste Générique\n");
    en_tete(&j1);
    ajout_droit(&j1,&a,sizeof(int *));a++;
    ajout_droit(&j1,&a,sizeof(int *));a++;
    ajout_droit(&j1,&a,sizeof(int *));a++;
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
        int * val;
        valeur_elt(p,&val,sizeof(int *));
        printf("%d ");
    }
    printf("\n");
}
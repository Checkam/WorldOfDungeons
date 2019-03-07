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
    printf("----- Programme de Test des Listes -----\n");

    /* Valeurs */
    int tab1[5] = {0,1,2,3,4};
    int tab2[5] = {5,6,7,8,9};

    /* Déclaration des listes */
    t_liste j1;
    t_liste j2;

    /* Création des listes */
    printf("\t-> Création des Listes\n");
    init_liste(&j1);
    init_liste(&j2);

    /* Remplissage des listes avec des valeurs quelconques */
    printf("\t-> Remplissage des Listes\n");
    remplir_liste(&j1,3,tab1);
    remplir_liste(&j1,5,tab2);

    /* Affichage des listes */
    printf("\t-> Affichage des Listes\n");
    afficher_liste(&j1);
    afficher_liste(&j2);

    /* Destruction des listes */
    printf("\t-> Destruction des Listes\n");
    detruire_liste(&j1);
    detruire_liste(&j1);

    return EXIT_SUCCESS;
}

void afficher_liste(t_liste * p)
{
    for(en_tete(p);!hors_liste(p);suivant(p))
    {
        int * tab;
        valeur_elt(p,&tab); // On récupère le tableau
        printf("[ "); // On l'affiche
        int i;
        for(i = 0; i < 5; i++)
            printf("%d ",tab[i]);
        printf("]");
    }
    printf("\n");
}

void remplir_liste(t_liste * p, int nb_val, int * val)
{
    en_tete(p);
    int i;
    for(i = 0; i < nb_val; ajout_droit(p,val),i++);
}
/**
 * \file test_donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 18/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
//#include <chemin.h>
//#include <SDL2/SDL.h>
#include <commun.h>
#include <donjon.h>

#define NB_SALLE 30

void init_tab(int tab[NB_SALLE][NB_SALLE]){
    int i, j;
    for(i = 0; i < NB_SALLE; i++){
        for(j = 0; j < NB_SALLE; j++){
            tab[i][j] = 0;
        }
    }
}

void aff_tab(int tab[NB_SALLE][NB_SALLE]){
    int i, j;
    for(i = 0; i < NB_SALLE; i++){
        for(j = 0; j < NB_SALLE; j++){
            if(tab[i][j])
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char **argv, char **env){

    if(argc != 2){
    	fprintf(stderr, "Usage:%s SEED\n", argv[0]);
        return EXIT_FAILURE;
    }

    SEED = atoi(argv[1]);

    t_liste *liste;
    int tab[NB_SALLE][NB_SALLE];

    donjon_creer(&liste, NB_SALLE);

    init_tab(tab);

    t_salle_donjon * salle;
    for(en_tete(liste); !hors_liste(liste); suivant(liste)){
        valeur_elt(liste, (void **)&salle);
        tab[salle->x][salle->y] = 1;
    }

    aff_tab(tab);
    donjon_detruire(&liste);


    return EXIT_SUCCESS;
}

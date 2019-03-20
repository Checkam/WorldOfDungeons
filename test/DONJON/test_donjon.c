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
#include <affichage.h>
#include <block.h>

#define NB_SALLE 10

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

void aff_salle(t_liste * salle){
    int i;
    t_block * tab = NULL;
    for(i = MAX_SCREEN; i >= 0; i--){
        for(en_tete(salle); !hors_liste(salle); suivant(salle)){
        
            valeur_elt(salle, &tab);
            if(tab[i].id == ROCHE)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");
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
        //aff_salle(salle->structure);
        AFF_map_term(salle->structure, 0, 0);
        tab[salle->x][salle->y] = 1;
    }

    aff_tab(tab);

    donjon_detruire(&liste);
    

    return EXIT_SUCCESS;
}

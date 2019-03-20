/**
 * \file donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 18/03/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <liste.h>
#include <erreur.h>
#include <commun.h>
#include <donjon.h>
#include <perlin.h>
#include <block.h>

#define FREQ 0.01
#define DEPTH 5

/**
 * \fn
 * \param
*/
t_erreur donjon_creer(t_liste ** liste, int nb_salle){
    /* Vérification */
    if(liste == NULL){
        erreur_save(PTR_NULL, "donjon_creer() : Double poiteur sur la liste NULL");
        return PTR_NULL;
    }
    if(nb_salle <= 0){
        erreur_save(VALUE_ERROR, "donjon_creer() : Nombre de salle inferieur ou égal à 0");
        return VALUE_ERROR;
    }

    /* Création Donjon */
    *liste = malloc(sizeof(t_liste));
    init_liste(*liste);

    /* Calcul taille donjon */
    int taille_donjon = nb_salle;

    /* Création Structure donjon */
    while(nb_salle--){
        donjon_ajout_salle(*liste, taille_donjon);
    }

    /* Création structure salle */
    t_salle_donjon * salle;
    for(en_tete(*liste); !hors_liste(*liste); suivant(*liste)){
        valeur_elt(*liste, (void **)&salle);
        donjon_creer_structure_salle(salle);
    }

    return OK;
}

/**
 * \fn
 * \param
*/
static t_erreur donjon_ajout_salle(t_liste * liste, int taille_donjon){
    /* Vérification */
    if(liste == NULL){
        erreur_save(PTR_NULL, "donjon_ajout_salle() : Poiteur sur la liste NULL");
        return PTR_NULL;
    }

    /* Création salle */
    t_salle_donjon * salle = NULL;

    if(liste_vide(liste)){
        donjon_creer_salle(&salle, taille_donjon / 2, taille_donjon / 2);
        ajout_droit(liste, salle);
        return OK;
    }

    /* On sélectionne une salle */
    int i = chercher_salle(liste);
    t_salle_donjon * tamp;
    valeur_liste(liste, i, (void **)&tamp);

    /* On sélectionne une case voisine */
    int choix;
    selection_voisin(tamp, &choix);

    int x = tamp->x;
    int y = tamp->y;
    if(choix == 0){
        x--;
    }else if(choix == 1){
        y--;
    }else if(choix == 2){
        x++;
    }else if(choix == 3){
        y++;
    }
    
    /* On crée la salle puis on l'ajoute à la liste */
    donjon_creer_salle(&salle, x, y);
    en_queue(liste);
    ajout_droit(liste, salle);
    update_voisin(liste, taille_donjon);

    return OK;
}

/**
 * \fn
 * \param
*/
static t_erreur donjon_creer_salle(t_salle_donjon ** salle, int x, int y){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_salle() : Doule pointeur sur la salle NULL");
        return PTR_NULL;
    }

    /* Création salle */
    *salle = malloc(sizeof(t_salle_donjon));
    (*salle)->x = x;
    (*salle)->y = y;
    int i;
    for(i = 0; i < 4; i++){
        (*salle)->voisin[i] = 0;
    }

    return OK;
}

/**
 * \fn
 * \param
*/
static int nb_voisin_salle(t_salle_donjon * salle){
    int nb = 0;
    if(salle == NULL)
        return nb;
    int i;
    for(i = 0; i < 4; i++)
        if(salle->voisin[i] == 0)
            nb++;
    
    return nb;
}

/**
 * \fn
 * \param
*/
static t_erreur selection_voisin(t_salle_donjon * salle, int * choix){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur salle NULL");
        return PTR_NULL;
    }
    if(choix == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur choix NULL");
        return PTR_NULL;
    }

    /* On sélectionne une salle inexistante */
    t_liste * liste = malloc(sizeof(t_liste));
    init_liste(liste);
    int i;
    for(i = 0; i < 4; i++){
        if(salle->voisin[i] == 0){
            int * tamp = malloc(sizeof(int));
            *tamp = i;
            ajout_droit(liste, (void *)tamp);
        }
    }

    srand(SEED * salle->x * salle->y);
    int choix_voisin;
    choix_voisin = rand() % taille_liste(liste);
    int *choix_inter;
    valeur_liste(liste, choix_voisin, (void **)&choix_inter);
    *choix = *choix_inter;

    /* On libère la mémoire */
    detruire_liste(liste, free);
    free(liste);
    
    return OK;
}

/**
 * \fn
 * \brief Cherche une salle ayant au moins 1 voisin
 * \param
 * \return La position dans la liste, -1 sinon
*/
static int chercher_salle(t_liste *liste){
    /* On sélectionne une salle aléatoire */
    int taille_l = taille_liste(liste);
    srand(SEED * taille_l);
    int i = rand() % taille_l;
    
    /* On cherche une salle ayant au moins 1 voisin */
    t_salle_donjon * salle;
    int verif = 0;
    while(!verif){
        valeur_liste(liste, i, (void **)&salle);

        if(nb_voisin_salle(salle) <= 0){
            if(i >= taille_l - 1)
                i = 0;
            else
                i++;            
        }else{
            verif = 1;
        }
    }
    return i;
}

/**
 * 
*/
static t_erreur update_voisin(t_liste * liste, int taille_donjon){
    t_salle_donjon *salle_courante, *salle_suivante;

    int i;
    for(i = 0; i < taille_liste(liste); i++){
        valeur_liste(liste, i, (void **)&salle_courante);

        for(en_tete(liste); !hors_liste(liste); suivant(liste)){
            valeur_elt(liste, (void **)&salle_suivante);
            if(salle_courante != salle_suivante){
                if(salle_courante->y == salle_suivante->y){
                    if(salle_courante->x - 1 == salle_suivante->x){
                        salle_courante->voisin[0] = 1;
                        salle_suivante->voisin[2] = 1;
                    }else if(salle_courante->x + 1 == salle_suivante->x){
                        salle_courante->voisin[2] = 1;
                        salle_suivante->voisin[0] = 1;
                    }
                }else if(salle_courante->x == salle_suivante->x){
                    if(salle_courante->y - 1 == salle_suivante->y){
                        salle_courante->voisin[1] = 1;
                        salle_suivante->voisin[3] = 1;
                    }else if(salle_courante->y + 1 == salle_suivante->y){
                        salle_courante->voisin[3] = 1;
                        salle_suivante->voisin[1] = 1;
                    }
                }
            }
            if(salle_courante->x == 0){
                salle_courante->voisin[0] = 1;
            }else if(salle_courante->x == taille_donjon - 1){
                salle_courante->voisin[2] = 1;
            }else if(salle_courante->y == 0){
                salle_courante->voisin[1] = 1;
            }else if(salle_courante->y == taille_donjon - 1){
                salle_courante->voisin[3] = 1;
            }
        }
    }

    return OK;
}

/**
 * 
*/
t_erreur donjon_creer_structure_salle(t_salle_donjon * salle){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_structure_salle() : Pointeur sur salle NULL");
        return PTR_NULL;
    }

    /* Initialisation structure salle */
    t_liste * liste = malloc(sizeof(t_liste));
    init_liste(liste);
    salle->structure = liste;

    /* Création structure salle */
    t_block * tab = NULL;
    int i;
    for(i = 0; i < SIZE; i++){
        tab = malloc(sizeof(t_block) * MAX_SCREEN);
        int hauteur;

        /* Génération relief plafond */
        hauteur = perlin2d(i, salle->x * salle->y, FREQ * 20, DEPTH) * (MAX_SCREEN) + (MAX_SCREEN / 4);
        if(hauteur >= MAX_SCREEN - 1)
            hauteur = MAX_SCREEN - 1;
        
        int j;
        for(j = MAX_SCREEN - 1; j >= 0; j--){
            tab[j].x = i;
            tab[j].y = j;
            if(j >= hauteur || i == 0 || i == SIZE - 1 || j == 0)
                tab[j].id = ROCHE;
            else
                tab[j].id = AIR;
        }
        en_queue(liste);
        ajout_droit(liste, tab);
    }

    return OK;
}

/**
 * 
*/
t_erreur donjon_detruire(t_liste **liste){
    /* Vérification */
    if(liste == NULL){
        erreur_save(PTR_NULL, "donjon_detruire() : Double pointeur sur liste NULL");
        return PTR_NULL;
    }
    if(*liste == NULL){
        return OK;
    }

    /* Destruction donjon */
    detruire_liste(*liste, (void *)donjon_detruire_salle);
    free(*liste);
    *liste = NULL;

    return OK;
}

/**
 * 
*/
void donjon_detruire_salle(t_salle_donjon *salle){
    if(salle != NULL){
        if(salle->structure != NULL){
            detruire_liste(salle->structure, free);
            salle->structure = NULL;
        }
        free(salle);
    }
}
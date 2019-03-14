/**
 * \file donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 13/03/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <liste.h>
#include <erreur.h>
#include <commun.h>
#include <donjon.h>
#include <math.h>


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
    int taille_donjon = sqrt(nb_salle) + 1;

    while(nb_salle--){
        donjon_ajout_salle(*liste, taille_donjon);
    }
    return OK;
}

/**
 * \fn
 * \param
*/
t_erreur donjon_ajout_salle(t_liste * liste, int taille_donjon){
    /* Vérification */
    if(liste == NULL){
        erreur_save(PTR_NULL, "donjon_ajout_salle() : Poiteur sur la liste NULL");
        return PTR_NULL;
    }

    /* Création salle */
    t_salle_donjon * salle;

    if(liste_vide(liste)){
        donjon_creer_salle(&salle, taille_donjon / 2, taille_donjon / 2);
        ajout_droit(liste, salle);
        return OK;
    }

    int taille_l = taille_liste(liste);
    srand(SEED * taille_l);
    int i = rand() % taille_l;

    t_salle_donjon * tamp;
    /* On cherche une salle qui a au moins un voisin */
    do{
        valeur_liste(liste, i, &tamp);
        srand(SEED * tamp->x * tamp->y);
        i = rand() % taille_l;
    }while(nb_voisin_salle(tamp) == 0);
    
    /* On sélectionne une case voisine */
    int choix;
    selection_voisin(tamp, &choix);

    tamp->voisin[choix] = 1;
    int x = tamp->x;
    int y = tamp->y;
    if(choix == 0)
        x--;
    else if(choix == 1)
        y--;
    else if(choix == 2)
        x++;
    else if(choix == 3)
        y++;
    
    donjon_creer_salle(&salle, x, y);

    return OK;
}

/**
 * \fn
 * \param
*/
t_erreur donjon_creer_salle(t_salle_donjon ** salle, int x, int y){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_salle() : Doule pointeur sur la salle NULL");
        return PTR_NULL;
    }
    if(*salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_salle() : Pointeur sur la salle NULL");
        return PTR_NULL;
    }

    /* Création salle */
    *salle = malloc(sizeof(t_salle_donjon));
    (*salle)->x = x;
    (*salle)->y = y;
    (*salle)->voisin[0] = v1;//gérer les voisins
    (*salle)->voisin[1] = v2;
    (*salle)->voisin[2] = v3;
    (*salle)->voisin[3] = v4;

    return OK;
}

/**
 * \fn
 * \param
*/
int nb_voisin_salle(t_salle_donjon * salle){
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
t_erreur selection_voisin(t_salle_donjon * salle, int * choix){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur salle NULL");
        return PTR_NULL;
    }
    if(choix == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur choix NULL");
        return PTR_NULL;
    }

    /* On sélectionne un voisin */
    t_liste * liste;
    init_liste(liste);
    int i;
    for(i = 0; i < 4; i++){
        if(salle->voisin[i] == 0){
            int * tamp = malloc(sizeof(int));
            *tamp = i;
            ajout_droit(liste, tamp);
        }
    }

    srand(SEED * taille_liste(liste));
    *choix = rand() % taille_liste(liste);//Gérer les salles en bords de map

    detruire_liste(liste, free);
    
    return OK;
}
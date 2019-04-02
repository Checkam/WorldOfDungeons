/**
 * \file donjon.h
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 26/03/2019
*/
#ifndef __DONJON_H__
#define __DONJON_H__

#include <erreur.h>
#include <liste.h>
#include <SDL2/SDL.h>
#include <entite.h>
#include <stdbool.h>

/**
 * \enum t_type_salle_donjon
 * \brief Contient les types des différentes salles d'un donjon
*/
typedef enum e_type_salle_donjon{
    DONJON_DEPART,
    DONJON_INTERMEDIAIRE,
    DONJON_FIN
} t_type_salle_donjon;

/**
 * \enum t_salle_difficulte
 * \brief Contient les différentes difficultés d'un donjon
*/
typedef enum e_salle_difficulte{
    AUCUNE,
    FACILE,
    MOYEN,
    DIFFICILE,
    FINAL
} t_salle_difficulte;

/**
 * \struct t_salle_donjon
 * \brief Contient toutes les informations d'une salle de donjon
*/
typedef struct s_salle_donjon{
    int x, y;
    t_liste * structure;
    int voisin[4]; //LEFT-TOP-RIGHT-BOTTOM

    t_type_salle_donjon type;
    t_salle_difficulte difficulte;

    bool completed;
    t_liste * mob;
}t_salle_donjon;

/**
 * \struct t_donjon
 * \brief Contient les données d'un donjon
*/
typedef struct s_donjon{
    int x_map_joueur, y_map_joueur;
    t_liste * donjon;
} t_donjon;


/*************************************/
/* Primitive de création d'un donjon */
/*************************************/
t_erreur donjon_creer(t_donjon ** donjon, int nb_salle, t_entite * joueur);


/*************************************/
/* Primitive d'affichage d'un donjon */
/*************************************/
t_erreur donjon_afficher_Term(t_donjon * donjon, t_entite * joueur);
t_erreur donjon_afficher_SDL(SDL_Renderer * renderer, t_donjon * donjon, t_entite * joueur);


/************************************/
/* Primitive de gestion d'un donjon */
/************************************/
t_erreur donjon_gestion(SDL_Renderer * renderer, t_donjon * donjon, t_entite * joueur, uint8_t *ks, double coef_fps);
t_erreur tab_fenetre(t_liste * donjon, SDL_Rect pos_perso, t_liste ** tab_fenetre);


/****************************************/
/* Primitive de destruction d'un donjon */
/****************************************/
t_erreur donjon_detruire(t_donjon **donjon);

#endif
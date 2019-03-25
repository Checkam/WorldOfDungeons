/**
 * \file donjon.h
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 25/03/2019
*/
#ifndef __DONJON_H__
#define __DONJON_H__

#include <erreur.h>
#include <liste.h>
#include <SDL2/SDL.h>
#include <entite.h>

typedef enum e_type_salle_donjon{
    DONJON_DEPART,
    DONJON_INTER,
    DONJON_FIN
} t_type_salle_donjon;

typedef struct s_salle_donjon{
    int x, y;
    t_liste * structure;
    int voisin[4]; //LEFT-TOP-RIGHT-BOTTOM
    t_type_salle_donjon type;
    
}t_salle_donjon;

typedef struct s_donjon{
    int x_map_joueur, y_map_joueur;
    t_liste * donjon;
} t_donjon;

/* Primitive de création d'un donjon */
t_erreur donjon_creer(t_donjon ** donjon, int nb_salle, t_entite * joueur);

/* Primitive d'affichage d'un donjon */
t_erreur donjon_afficher_Term(t_donjon * donjon, SDL_Rect pos_perso);
t_erreur donjon_afficher_SDL(SDL_Renderer * renderer, t_donjon * donjon, SDL_Rect pos_perso);

/* Primitive de gestion d'un donjon */


/* Primitive de destruction d'un donjon */
t_erreur donjon_detruire(t_donjon **donjon);

#endif
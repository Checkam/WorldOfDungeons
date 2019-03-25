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

typedef struct s_salle_donjon{
    int x, y;
    t_liste * structure;
    int voisin[4]; //LEFT-TOP-RIGHT-BOTTOM
}t_salle_donjon;

/* Primitive de création d'un donjon */
t_erreur donjon_creer(t_liste ** liste, int nb_salle);

/* Primitive d'affichage d'un donjon */
t_erreur donjon_afficher_Term(t_liste * donjon, SDL_Rect pos_perso);
t_erreur donjon_afficher_SDL(SDL_Renderer * renderer, t_liste * donjon, SDL_Rect pos_perso);

/* Primitive de gestion d'un donjon */


/* Primitive de destruction d'un donjon */
t_erreur donjon_detruire(t_liste **liste);

#endif
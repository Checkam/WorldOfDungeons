/**
 *   \file affichage.h
 *   \brief Module d'affichage d'une liste de block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <liste.h>
#include <SDL2/SDL.h>


/* Fenetre */
int AFF_RectInWindow(SDL_Rect r);
int AFF_GetMidHeight(t_liste *list);

void AFF_map_sdl(t_liste *list,SDL_Renderer *renderer, int min);

/* Terminale */
void AFF_map_term(t_liste *list,int min, int max);

#endif

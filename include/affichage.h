#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <liste.h>
#include <SDL2/SDL.h>


/* Fenetre */
int dansFenetre(SDL_Rect r);
SDL_Texture * TextureBlock(int id,void *);
void aff_map_sdl(t_liste *list,SDL_Renderer *renderer,void *, int min);
int taille_mid_aff(t_liste *list);

/* Terminale */
char * CouleurBlock(int id, void *);
void aff_map(t_liste *list,int min, int max, void *);

#endif

/**
 * \file outils.h
 * \brief Contient une boite à outils de primitives de fonctions utiles
 * \author Jasmin GALBRUN
 * \date 09/03/2019
 * \version 1
*/
#ifndef __OUTILS_SDL_H__
#define __OUTILS_SDL_H__

#include <SDL2/SDL.h>
#include <erreur.h>

typedef enum e_type_dessin_texte{
    SOLID,
    SHADED,
    BLENDED
}t_type_dessin_texte;

t_erreur Create_IMG_Texture(SDL_Renderer * renderer, char * chemin_img, SDL_Texture * *texture_dest);
t_erreur Create_Text_Texture(SDL_Renderer * renderer, char * texte, char * chemin_police, int taille_police, SDL_Color couleur, t_type_dessin_texte type, SDL_Texture * *texture_dest);

#endif
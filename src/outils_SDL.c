/**
 * \file outils.c
 * \brief Contient une boite à outils de fonctions utiles
 * \author Jasmin GALBRUN
 * \date 09/03/2019
 * \version 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <erreur.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <outils_SDL.h>

/**
 * \fn t_erreur Create_IMG_Texture(SDL_Renderer * renderer, char * chemin_img, SDL_Texture * *texture_dest)
 * \brief Créé la texture correspondant à l'image passé en paramètre
 * \param renderer
 * \param chemin_img chemin de l'image
 * \param texture_dest Texture de destination de l'image
 * \return Code erreur
*/
t_erreur Create_IMG_Texture(SDL_Renderer * renderer, char * chemin_img, SDL_Texture * *texture_dest){
    /* Vérification */
    if(renderer == NULL){
        return PTR_NULL;
    }
    if(texture_dest == NULL){
        return PTR_NULL;
    }

    /* Création Surface */
    SDL_Surface * image = IMG_Load(chemin_img);
    if(image == NULL){
        return PTR_NULL;
    }

    /* création Texture */
    *texture_dest = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(*texture_dest == NULL){
        return PTR_NULL;
    }
    return OK;
}

/**
 * \fn t_erreur Create_Text_Texture(SDL_Renderer * renderer, char * texte, char * chemin_police, int taille_police, SDL_Color couleur, t_type_dessin_texte type, SDL_Texture * *texture_dest)
 * \brief Créé la texture correspondant au texte passé en paramètre
 * \param renderer
 * \param texte texte que l'on veut afficher
 * \param chemin_police police de caractère du texte
 * \param taille_police taille de la police
 * \param couleur couleur du texte
 * \param type type d'affichage du texte
 * \param texture_dest Texture de destination du texte
 * \return Code erreur 
*/
t_erreur Create_Text_Texture(SDL_Renderer * renderer, char * texte, char * chemin_police, int taille_police, SDL_Color couleur, t_type_dessin_texte type, SDL_Texture * *texture_dest){
    /* Vérification */
    if(renderer == NULL){
        return PTR_NULL;
    }
    if(texture_dest == NULL){
        return PTR_NULL;
    }

    /* Création police */
    TTF_Font *police = TTF_OpenFont(chemin_police, taille_police);
    if(police == NULL){
        printf("%s\n", TTF_GetError());
        return PTR_NULL;
    }

    /* Création Surface */
    SDL_Surface * texte_surface = NULL;
    if(type == BLENDED){
        texte_surface = TTF_RenderText_Blended(police, texte, couleur);
    }else{
        return TYPE_ERROR;
    }
    if(texte_surface == NULL){
        return PTR_NULL;
    }

    /* Création Texture */
    *texture_dest = SDL_CreateTextureFromSurface(renderer, texte_surface);
    if(*texture_dest == NULL){
        return PTR_NULL;
    }

    /* Destruction pointeur */
    SDL_FreeSurface(texte_surface);
    TTF_CloseFont(police);

    return OK;
}

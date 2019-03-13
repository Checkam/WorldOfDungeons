/**
 * \file menu.h
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 2
 * \date 13/03/2019
*/
#ifndef __MENU_H__
#define __MENU_H__

#include <SDL2/SDL.h>
#include <erreur.h>

/**
 * \enum t_type_menu
 * \brief Contient les différents types de menus possibles
*/
typedef enum e_type_menu {
    PRINCIPAL,
    SOLO,
    MULTIJOUEUR,
    OPTION,
    PAUSE,
    NOUVEAU_MENU,
    MENU_NULL
} t_type_menu;

/**
 * \struct t_bouton_menu
 * \brief Contient les informations d'un bouton
*/
typedef struct s_bouton_menu{
    int x, y, width, height;
    char * titre;
    SDL_Texture * texture;
    int state, focus;
    t_type_menu suivant;
} t_bouton_menu;

/**
 * \struct t_menu
 * \brief Contient l'ensemble des boutons appartenant au menu
*/
typedef struct s_menu{
    t_bouton_menu *(*tab_bouton);
    int nb_bouton;
    SDL_Texture * fond;
    int width, height;
}t_menu;

/* Primitive de création d'un menu */
t_erreur menu_ajout_bouton(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture, t_type_menu type);
t_erreur menu_creer(t_type_menu type, int width, int height, SDL_Texture * texture_bouton, SDL_Texture * fond, t_menu ** menu);

/* Primitive d'affichage d'un menu */
t_erreur menu_afficher_SDL(t_menu * menu, SDL_Renderer * renderer, SDL_Color couleur_texte);

/* Primitive de destruction d'un menu */
t_erreur menu_detruire_bouton(t_bouton_menu ** btn);
t_erreur menu_detruire(t_menu ** menu);

/* Primitive de gestion du menu */
t_erreur menu_gestion_SDL(t_menu * menu, SDL_MouseButtonEvent mouse, int * pos_btn_pressed);
t_erreur menu_suivant(t_menu ** menu, int pos_btn_pressed);

#endif
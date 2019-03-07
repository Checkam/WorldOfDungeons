/**
 * \file menu.h
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 07/03/2019
*/
#ifndef __MENU_H__
#define __MENU_H__

#include <ctype.h>
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
    NOUVEAU_MENU
} t_type_menu;

/**
 * \struct t_bouton_menu
 * \brief Contient les informations d'un bouton
*/
typedef struct s_bouton_menu{
    int x, y, width, height;
    char * titre;
    SDL_Texture * texture;
} t_bouton_menu;

/**
 * \struct t_menu
 * \brief Contient l'ensemble des boutons appartenant au menu
*/
typedef struct s_menu{
    t_bouton_menu *(*tab_bouton);
    int nb_bouton;
}t_menu;

/* Primitive de création d'un menu */
t_erreur ajout_bouton_menu(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture);
t_erreur creer_menu(t_type_menu type, int width, int height, t_menu ** menu);

t_erreur afficher_menu_test(t_menu * menu);

#endif

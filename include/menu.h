/**
 * \file menu.h
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 3
 * \date 15/03/2019
*/
#ifndef __MENU_H__
#define __MENU_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <erreur.h>

/**
 * \enum t_type_menu
 * \brief Contient les différents types de menus possibles
*/
typedef enum e_type_menu {
    MENU_PRINCIPAL,
    MENU_SOLO,
    MENU_MULTIJOUEUR,
    MENU_OPTION,
    MENU_PAUSE,
    NOUVEAU_MENU,
    MENU_NULL,
    MENU_NOUVELLE_PARTIE,
    MENU_CHARGER_PARTIE,
    MENU_QUITTER
} t_type_menu;

/**
 * \struct t_bouton_menu
 * \brief Contient les informations d'un bouton
*/
typedef struct s_bouton_menu{
    int x, y, width, height;
    char * titre;
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
    int width, height;
    t_type_menu type;
}t_menu;

/* Primitive Initialisation + Finalisation d'un menu */
t_erreur menu_init(SDL_Renderer * renderer);
t_erreur menu_quit(void);

/* Primitive de création d'un menu */
t_erreur menu_ajout_bouton(t_menu * menu, SDL_Rect rect, char * titre, t_type_menu type);
t_erreur menu_creer(t_type_menu type, int width, int height, t_menu ** menu);

/* Primitive d'affichage d'un menu */
t_erreur menu_afficher_SDL(t_menu * menu, SDL_Renderer * renderer);

/* Primitive de destruction d'un menu */
t_erreur menu_detruire_bouton(t_bouton_menu ** btn);
t_erreur menu_detruire(t_menu ** menu);

/* Primitive de gestion du menu */
t_erreur menu_gestion_SDL(t_menu * menu, int mouseState, t_type_menu * type_menu_suivant);
t_erreur menu_suivant(t_menu ** menu, t_type_menu type_menu_suivant);

#endif
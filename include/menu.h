/**
 * \file menu.h
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 07/03/2019
*/

#include <ctype.h>
#include <SDL2/SDL.h>

/**
 * \enum t_type_menu
 * \brief Contient les différents types de menus possibles
*/
typedef enum e_type_menu {
    PRINCIPAL,
    SOLO,
    MULTIJOUEUR,
    OPTION,
    PAUSE
} t_type_menu;

/**
 * \struct t_bouton_menu
 * \brief Contient les informations d'un bouton
*/
typedef struct s_bouton_menu{
    uint16_t x, y, width, height;
    char * titre;
    SDL_Texture * texture;
} t_bouton_menu;

/**
 * \struct t_menu
 * \brief Contient l'ensemble des boutons appartenant au menu
*/
typedef struct s_menu{
    t_bouton_menu * tab_bouton;
    Uint8_t nb_bouton;
}t_menu;

/* Primitive de création d'un menu */
t_erreur ajout_bouton_menu(t_menu * menu, uint16_t x, uint16_t y, uint16_t width, uint16_t height, char * titre, SDL_Texture * texture);
t_erreur creer_menu(t_type_menu type, uint16_t width, uint16_t height, t_menu * menu);
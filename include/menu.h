/**
 * \file menu.h
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 05/03/2019
*/

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
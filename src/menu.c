/**
 * \file menu.c
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 05/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <erreur.h>
#include <menu.h>

/**
 * \struct t_bouton_menu
 * \brief Contient les informations d'un bouton
*/
typedef struct s_bouton_menu{
    Uint16_t x, y, width, height;
    char * titre;
} t_bouton_menu;

/**
 * \struct t_menu
 * \brief Contient l'ensemble des boutons appartenant au menu
*/
typedef struct s_menu{
    t_bouton_menu * tab_bouton;
    Uint8_t nb_bouton;
}t_menu;

t_menu * menu = NULL;


/**
 * \fn t_erreur ajout_bouton_menu(Uint16_t x, Uint16_t y, Uint16_t width, Uint16_t height, char * titre)
 * \param 
*/
t_erreur ajout_bouton_menu(Uint16_t x, Uint16_t y, Uint16_t width, Uint16_t height, char * titre){
    if(menu == NULL){
        return UNDEFINED_MENU;
    }

    t_bouton_menu * btn = malloc(sizeof(t_bouton_menu));
    btn->titre = malloc(sizeof(char) * (strlen(titre) + 1));
    
    strcpy(btn->titre, titre);
    btn->x = x;
    btn->y = y;
    btn->width = width;
    btn->height = height;

    menu->tab_bouton[menu->nb_bouton] = btn;
    menu->nb_bouton++;

    return OK;
}

t_erreur creer_menu(t_type_menu type, Uint16_t width, Uint16_t height){
    
}
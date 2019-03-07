/**
 * \file menu.c
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 07/03/2019
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


/**
 * \fn t_erreur ajout_bouton_menu(t_menu * menu, Uint16_t x, Uint16_t y, Uint16_t width, Uint16_t height, char * titre)
 * \param 
*/
t_erreur ajout_bouton_menu(t_menu * menu, Uint16_t x, Uint16_t y, Uint16_t width, Uint16_t height, char * titre, SDL_Texture * texture){
    if(menu == NULL){
        return UNDEFINED_MENU;
    }

    t_bouton_menu * btn = malloc(sizeof(t_bouton_menu));

    if(titre != NULL){
        btn->titre = malloc(sizeof(char) * (strlen(titre) + 1));
        strcpy(btn->titre, titre);
    }
    btn->x = x;
    btn->y = y;
    btn->width = width;
    btn->height = height;

    if(texture == NULL){
        //valeur par défaut de la texture d'un bouton
    }else{
        btn->texture = texture;
    }

    menu->tab_bouton[menu->nb_bouton] = btn;
    menu->nb_bouton++;

    return OK;
}

/**
 * \fn t_erreur creer_menu(t_type_menu type, Uint16_t width, Uint16_t height, t_menu * menu)
 * \param 
*/
t_erreur creer_menu(t_type_menu type, Uint16_t width, Uint16_t height, t_menu * menu){
    int w, h; //Taille d'une colonne et d'une ligne

    menu = malloc(sizeof(t_menu));
    menu->nb_bouton = 0;

    if(type == PRINCIPAL){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu) * 4); //4 correspond au nombre de boutons dans le menu principal

        w = width / 3;
        h = height / 15;
        ajout_bouton_menu(w, 5 * h, w, 2 * h, "Solo", NULL);
        ajout_bouton_menu(w, 7 * h, w, 2 * h, "Multijoueur", NULL);
        ajout_bouton_menu(w, 9 * h, w, 2 * h, "Option", NULL);
        ajout_bouton_menu(w, 11 * h, w, 2 * h, "Quitter", NULL);
    }else if(type == SOLO){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu) * 3);

        w = width / 3;
        h = height / 14;
        ajout_bouton_menu(w, , w, 2 * h, "Nouvelle partie", NULL);
        ajout_bouton_menu(w, , w, 2 * h, "charger une partie", NULL);
        ajout_bouton_menu(w, , w, 2 * h, "Retour", NULL);
    }else{
        menu->tab_bouton = NULL;
    }
}
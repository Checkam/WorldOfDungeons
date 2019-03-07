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
#include <ctype.h>
#include <SDL2/SDL.h>
#include <erreur.h>
#include <menu.h>


/**
 * \fn t_erreur ajout_bouton_menu(t_menu * menu, uint16_t x, uint16_t y, uint16_t width, uint16_t height, char * titre, SDL_Texture * texture)
 * \param 
*/
t_erreur ajout_bouton_menu(t_menu * menu, uint16_t x, uint16_t y, uint16_t width, uint16_t height, char * titre, SDL_Texture * texture){
    if(menu == NULL){
        return UNDEFINED_MENU;
    }

    /* On ajoute un bouton au menu */
    if(menu->tab_bouton == NULL){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu));
    }else{
        menu->tab_bouton = realloc(menu->tab_bouton, (menu->nb_bouton + 1) * sizeof(t_bouton_menu));
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
        btn->texture = NULL;
    }else{
        btn->texture = texture;
    }

    menu->tab_bouton[menu->nb_bouton] = btn;
    menu->nb_bouton++;

    return OK;
}

/**
 * \fn t_erreur creer_menu(t_type_menu type, uint16_t width, uint16_t height, t_menu * menu)
 * \param 
*/
t_erreur creer_menu(t_type_menu type, uint16_t width, uint16_t height, t_menu * menu){
    int w, h; //Taille d'une colonne et d'une ligne

    menu = malloc(sizeof(t_menu));
    menu->nb_bouton = 1;

    if(type == PRINCIPAL){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu));

        w = width / 3;
        h = height / 15;
        ajout_bouton_menu(w, 5 * h, w, 2 * h, "Solo", NULL, menu);
        ajout_bouton_menu(w, 7 * h, w, 2 * h, "Multijoueur", NULL, menu);
        ajout_bouton_menu(w, 9 * h, w, 2 * h, "Option", NULL, menu);
        ajout_bouton_menu(w, 11 * h, w, 2 * h, "Quitter", NULL, menu);
    }else if(type == SOLO){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu));

        w = width / 3;
        h = height / 15;
        ajout_bouton_menu(w, 6 * h, w, 2 * h, "Nouvelle partie", NULL, menu);
        ajout_bouton_menu(w, 8 * h, w, 2 * h, "charger une partie", NULL, menu);
        ajout_bouton_menu(w, 10 * h, w, 2 * h, "Retour", NULL, menu);
    }else{
        menu->tab_bouton = NULL;
    }

    return OK;
}
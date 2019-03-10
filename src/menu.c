/**
 * \file menu.c
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 1
 * \date 10/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <menu.h>
#include <outils_SDL.h>
#include <chemin.h>

#define POLICE_MENU "data/police/8-BIT_WONDER.ttf"

/**
 * \fn t_erreur ajout_bouton_menu(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture)
 * \param menu Pointeur sur un t_menu
 * \param x Position en x du bouton
 * \param y Position en y du bouton
 * \param width Largeur du bouton
 * \param height Hauteur du bouton
 * \return Retourne un code erreur
*/
t_erreur ajout_bouton_menu(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture){
    /* Vérification */
    if(menu == NULL){
        return UNDEFINED_MENU;
    }
    if(x < 0 || y < 0 || width < 0 || height < 0){
        return VALUE_ERROR;
    }

    /* Allocation de la mémoire pour un bouton au menu */
    if(menu->tab_bouton == NULL){
        menu->tab_bouton = malloc(sizeof(t_bouton_menu));
    }else{
        menu->tab_bouton = realloc(menu->tab_bouton, (menu->nb_bouton + 1) * sizeof(t_bouton_menu));
    }

    /* Création d'un bouton */
    t_bouton_menu * btn = malloc(sizeof(t_bouton_menu));

    if(titre != NULL){
        btn->titre = malloc(sizeof(char) * (strlen(titre) + 1));
        strcpy(btn->titre, titre);
    }
    btn->x = x;
    btn->y = y;
    btn->width = width;
    btn->height = height;
    btn->state = SDL_RELEASED;
    btn->focus = 0;

    if(texture == NULL){
        //valeur par défaut de la texture d'un bouton
        btn->texture = NULL;
    }else{
        btn->texture = texture;
    }

    /* Ajout du bouton au menu */
    menu->tab_bouton[menu->nb_bouton] = btn;
    menu->nb_bouton++;

    return OK;
}

/**
 * \fn t_erreur creer_menu(t_type_menu type, int width, int height, SDL_Texture * texture, t_menu ** menu)
 * \param type Type de menu que l'on veut avoir (Solo,...)
 * \param width Largeur de la fenêtre d'affichage
 * \param height Hauteur de la fenêtre d'affichage
 * \param menu Double pointeur sur le menu que l'on veut créer
 * \return Retourne un code erreur
*/
t_erreur creer_menu(t_type_menu type, int width, int height, SDL_Texture * texture, t_menu ** menu){
    int w, h; //Taille d'une colonne et d'une ligne

    if(width < 0 || height < 0){
        return VALUE_ERROR;
    }
    
    /* Création d'un menu */
    *menu = malloc(sizeof(t_menu));
    (*menu)->nb_bouton = 0;
    
    if(type == PRINCIPAL){
        (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));
        
        w = width / 3;
        h = height / 15;
        ajout_bouton_menu(*menu, w, 3 * h, w, 2 * h, "Solo", texture);
        ajout_bouton_menu(*menu, w, 5 * h, w, 2 * h, "Multijoueur", texture);
        ajout_bouton_menu(*menu, w, 7 * h, w, 2 * h, "Option", texture);
        ajout_bouton_menu(*menu, w, 9 * h, w, 2 * h, "Quitter", texture);
    }else if(type == SOLO){
        (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));

        w = width / 4;
        h = height / 15;
        ajout_bouton_menu(*menu, w, 5 * h, 2 * w, 2 * h, "Nouvelle partie", texture);
        ajout_bouton_menu(*menu, w, 7 * h, 2 * w, 2 * h, "charger une partie", texture);
        ajout_bouton_menu(*menu, w, 9 * h, 2 * w, 2 * h, "Retour", texture);
    }else if(type == NOUVEAU_MENU){
        (*menu)->tab_bouton = NULL;
    }else{
        return INCORRECT_MENU_TYPE;
    }

    return OK;
}

/**
 * \fn t_erreur SDL_afficher_menu(t_menu * menu, SDL_Renderer * renderer, SDL_Color couleur_texte)
 * \param menu Pointeur sur le menu que l'on veut afficher
 * \param renderer Renderer sur le lequel on veut afficher le menu
 * \param couleur_texte Couleur du texte
 * \return Code erreur
*/
t_erreur SDL_afficher_menu(t_menu * menu, SDL_Renderer * renderer, SDL_Color couleur_texte){
    /* Vérification */
    if(menu == NULL){
        return UNDEFINED_MENU;
    }
    if(renderer == NULL){
        return PTR_NULL;
    }
    if(menu->tab_bouton == NULL){
        return PTR_NULL;
    }

    /* Initialisation */
    char * police;
    creation_chemin(POLICE_MENU, &police);
    SDL_Texture * texte_tex;
    
    /* Définition taille de la police */
    int taille_max_titre = 0;
    int i;
    for(i = 0; i < menu->nb_bouton; i++){
        if(strlen(menu->tab_bouton[i]->titre) > taille_max_titre)
            taille_max_titre = strlen(menu->tab_bouton[i]->titre);
    }
    int taille_police = menu->tab_bouton[0]->width / taille_max_titre;

    /* Affichage */
    for(i = 0; i < menu->nb_bouton; i++){
        SDL_Rect r_img = {
            menu->tab_bouton[i]->x,
            menu->tab_bouton[i]->y,
            menu->tab_bouton[i]->width,
            menu->tab_bouton[i]->height
        };

        /* Centrer le texte */
        int x_txt = (menu->tab_bouton[i]->width - taille_police * strlen(menu->tab_bouton[i]->titre)) / 2 + menu->tab_bouton[i]->x;
        int y_txt = (menu->tab_bouton[i]->height - taille_police) / 2 + menu->tab_bouton[i]->y;
        SDL_Rect r_txt = {
            x_txt,
            y_txt,
            taille_police * strlen(menu->tab_bouton[i]->titre),
            taille_police
        };

        /* Etat bouton */
        if(menu->tab_bouton[i]->focus == 1){
            couleur_texte.a = 100;
        }else{
            couleur_texte.a = 255;
        }
        
        Create_Text_Texture(renderer, menu->tab_bouton[i]->titre, police, taille_police, couleur_texte, BLENDED, &texte_tex);

        SDL_RenderCopy(renderer, menu->tab_bouton[i]->texture, NULL, &r_img);
        SDL_RenderCopy(renderer, texte_tex, NULL, &r_txt);

        SDL_DestroyTexture(texte_tex);
    }
    free(police);
    return OK;
}

/**
 * \fn t_erreur detruire_bouton_menu(t_bouton_menu ** btn)
 * \param btn Bouton que l'on veut détruire
 * \return Code erreur
*/
t_erreur detruire_bouton_menu(t_bouton_menu ** btn){
    if(*btn != NULL){
        if((*btn)->titre != NULL){
            free((*btn)->titre);
        }
        (*btn)->titre = NULL;
        free(*btn);
        *btn = NULL;
    }
    return OK;
}

/**
 * \fn t_erreur detruire_bouton_menu(t_menu ** menu)
 * \param menu Menu que l'on veut détruire
 * \return Code erreur
*/
t_erreur detruire_menu(t_menu ** menu){
    if(*menu != NULL){
        if((*menu)->tab_bouton != NULL){
            int i;
            for(i = 0; i < (*menu)->nb_bouton; i++){
                detruire_bouton_menu(&((*menu)->tab_bouton[i]));
            }
            free((*menu)->tab_bouton);
            (*menu)->tab_bouton = NULL;
        }
        free(*menu);
        *menu = NULL;
    }
    return OK;
}

/**
 * \fn t_erreur gestion_bouton_menu(t_menu * menu, int mouseX, int mouseY)
 * \param menu Menu que l'on veut gérer
 * \param mouseX Position en X de la souris
 * \param mouseY position en Y de la souris
 * \return Code erreur
*/
t_erreur gestion_menu_SDL(t_menu * menu, SDL_MouseButtonEvent mouse, int * pos_btn_pressed){
    /* Vérification */
    if(menu == NULL){
        return PTR_NULL;
    }
    if(menu->tab_bouton == NULL){
        return PTR_NULL;
    }
    if(pos_btn_pressed == NULL){
        return PTR_NULL;
    }

    /* Gestion souris menu */
    *pos_btn_pressed = -1;
    int i;
    for(i = 0; i < menu->nb_bouton; i++){
        SDL_Rect r = {
            menu->tab_bouton[i]->x,
            menu->tab_bouton[i]->y,
            menu->tab_bouton[i]->width,
            menu->tab_bouton[i]->height
        };
        SDL_Point p = {
            mouse.x,
            mouse.y
        };
        if(SDL_PointInRect(&p, &r)){
            menu->tab_bouton[i]->focus = 1;
            if(menu->tab_bouton[i]->state == SDL_PRESSED && mouse.state == SDL_RELEASED){
                *pos_btn_pressed = i;
                menu->tab_bouton[i]->state = SDL_RELEASED;
            }else if(mouse.state == SDL_PRESSED){
                menu->tab_bouton[i]->state = SDL_PRESSED;
            }
        }else{
            menu->tab_bouton[i]->focus = 0;
        }
    }


    return OK;
}
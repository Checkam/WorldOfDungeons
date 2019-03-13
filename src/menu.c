/**
 * \file menu.c
 * \brief Gestion du menu (solo, multijoueur, ...)
 * \author Jasmin GALBRUN
 * \version 2
 * \date 13/03/2019
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
 * \fn t_erreur menu_ajout_bouton(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture, t_type_menu type)
 * \param menu Pointeur sur un t_menu
 * \param x Position en x du bouton
 * \param y Position en y du bouton
 * \param width Largeur du bouton
 * \param height Hauteur du bouton
 * \param titre Titre du bouton
 * \param texture Texture du bouton
 * \param type Type du menu suivant
 * \return Retourne un code erreur
*/
t_erreur menu_ajout_bouton(t_menu * menu, int x, int y, int width, int height, char * titre, SDL_Texture * texture, t_type_menu type){
    /* Vérification */
    if(menu == NULL){
        erreur_save(PTR_NULL, "menu_ajout_bouton() : Pointeur sur le menu NULL");
        return PTR_NULL;
    }
    if(x < 0 || y < 0 || width < 0 || height < 0){
        erreur_save(VALUE_ERROR, "menu_ajout_bouton() : Position ou taille des boutons incorrects");
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
    btn->suivant = type;

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
 * \fn t_erreur menu_creer(t_type_menu type, int width, int height, SDL_Texture * texture_bouton, SDL_Texture * fond, t_menu ** menu)
 * \param type Type de menu que l'on veut avoir (Solo,...)
 * \param width Largeur de la fenêtre d'affichage
 * \param height Hauteur de la fenêtre d'affichage
 * \param texture_bouton Texture des boutons du menu
 * \param fond Texture d'arrière plan du menu
 * \param menu Double pointeur sur le menu que l'on veut créer
 * \return Retourne un code erreur
*/
t_erreur menu_creer(t_type_menu type, int width, int height, SDL_Texture * texture_bouton, SDL_Texture * fond, t_menu ** menu){
    /* Vérification */
    if(width < 0 || height < 0){
        erreur_save(VALUE_ERROR, "menu_creer() : Taille du menu incorrect");
        return VALUE_ERROR;
    }
    if(menu == NULL){
        erreur_save(PTR_NULL, "menu_creer() : Pointeur sur le menu NULL");
        return PTR_NULL;
    }
    
    /* Création d'un menu */
    if(type == MENU_NULL){
        *menu = NULL;
        return OK;
    }
    *menu = malloc(sizeof(t_menu));
    (*menu)->nb_bouton = 0;
    (*menu)->fond = fond;
    (*menu)->width = width;
    (*menu)->height = height;
    
    int w, h; //Taille d'une colonne et d'une ligne
    if(type == PRINCIPAL){
        (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));
        
        w = width / 3;
        h = height / 15;
        menu_ajout_bouton(*menu, w, 3 * h, w, 2 * h, "Solo", texture_bouton, SOLO);
        menu_ajout_bouton(*menu, w, 5 * h, w, 2 * h, "Multijoueur", texture_bouton, MENU_NULL);
        menu_ajout_bouton(*menu, w, 7 * h, w, 2 * h, "Option", texture_bouton, MENU_NULL);
        menu_ajout_bouton(*menu, w, 9 * h, w, 2 * h, "Quitter", texture_bouton, MENU_NULL);
    }else if(type == SOLO){
        (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));

        w = width / 4;
        h = height / 15;
        menu_ajout_bouton(*menu, w, 5 * h, 2 * w, 2 * h, "Nouvelle partie", texture_bouton, MENU_NULL);
        menu_ajout_bouton(*menu, w, 7 * h, 2 * w, 2 * h, "charger une partie", texture_bouton, MENU_NULL);
        menu_ajout_bouton(*menu, w, 9 * h, 2 * w, 2 * h, "Retour", texture_bouton, PRINCIPAL);
    }else if(type == NOUVEAU_MENU){
        (*menu)->tab_bouton = NULL;
    }else{
        erreur_save(INCORRECT_MENU_TYPE, "menu_creer() : Type de menu incorrect");
        return INCORRECT_MENU_TYPE;
    }

    return OK;
}

/**
 * \fn t_erreur menu_afficher_SDL(t_menu * menu, SDL_Renderer * renderer, SDL_Color couleur_texte)
 * \param menu Pointeur sur le menu que l'on veut afficher
 * \param renderer Renderer sur le lequel on veut afficher le menu
 * \param couleur_texte Couleur du texte
 * \return Code erreur
*/
t_erreur menu_afficher_SDL(t_menu * menu, SDL_Renderer * renderer, SDL_Color couleur_texte){
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
    if(menu->fond != NULL){
        SDL_Rect fenetre = {
            0,
            0,
            menu->width,
            menu->height
        };
        SDL_RenderCopy(renderer, menu->fond, NULL, &fenetre);
    }
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
 * \fn
 * \param
*/
t_erreur menu_afficher_Term(t_menu * menu){
    /* Vérification */
    return OK;
}

/**
 * \fn t_erreur menu_detruire_bouton(t_bouton_menu ** btn)
 * \param btn Bouton que l'on veut détruire
 * \return Code erreur
*/
t_erreur menu_detruire_bouton(t_bouton_menu ** btn){
    if(*btn != NULL){
        if((*btn)->titre != NULL){
            free((*btn)->titre);
            (*btn)->titre = NULL;
        }
        free(*btn);
        *btn = NULL;
    }
    return OK;
}

/**
 * \fn t_erreur menu_detruire(t_menu ** menu)
 * \param menu Menu que l'on veut détruire
 * \return Code erreur
*/
t_erreur menu_detruire(t_menu ** menu){
    if(*menu != NULL){
        if((*menu)->tab_bouton != NULL){
            int i;
            for(i = 0; i < (*menu)->nb_bouton; i++){
                menu_detruire_bouton(&((*menu)->tab_bouton[i]));
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
 * \fn t_erreur menu_gestion_SDL(t_menu * menu, SDL_MouseButtonEvent mouse, int * pos_btn_pressed)
 * \param menu Menu que l'on veut gérer
 * \param mouse Info de la souris
 * \param pos_btn_pressed Pointeur sur la position du bouton cliquer, -1 sinon
 * \return Code erreur
*/
t_erreur menu_gestion_SDL(t_menu * menu, SDL_MouseButtonEvent mouse, int * pos_btn_pressed){
    /* Vérification */
    if(menu == NULL){
        erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le menu NULL");
        return PTR_NULL;
    }
    if(menu->tab_bouton == NULL){
        erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le tab_bouton NULL");
        return PTR_NULL;
    }
    if(pos_btn_pressed == NULL){
        erreur_save(PTR_NULL, "menu_gestion_SDL() : Pointeur sur le pos_btn_pressed NULL");
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

/**
 * \fn t_erreur menu_suivant(t_menu ** menu, int pos_btn_pressed)
 * \param menu Double pointeur sur le menu
 * \param pos_btn_pressed Position du bouton
 * \return Code erreur
*/
t_erreur menu_suivant(t_menu ** menu, int pos_btn_pressed){
    /* Vérification */
    if(menu == NULL){
        erreur_save(PTR_NULL, "menu_suivant() : Double pointeur sur le menu NULL");
        return PTR_NULL;
    }
    if(*menu == NULL){
        erreur_save(PTR_NULL, "menu_suivant() : Pointeur sur le menu NULL");
        return PTR_NULL;
    }
    if(pos_btn_pressed < 0 || pos_btn_pressed >= (*menu)->nb_bouton){
        erreur_save(VALUE_ERROR, "menu_suivant() : Position du bouton incorrecte");
        return VALUE_ERROR;
    }

    /* Création + destruction du menu */
    t_menu * tamp;
    menu_creer((*menu)->tab_bouton[pos_btn_pressed]->suivant, (*menu)->width, (*menu)->height, (*menu)->tab_bouton[pos_btn_pressed]->texture, (*menu)->fond, &tamp);
    menu_detruire(menu);
    *menu = tamp;

    return OK;
}
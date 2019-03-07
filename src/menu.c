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
#include <SDL2/SDL_ttf.h>
#include <menu.h>

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
        ajout_bouton_menu(*menu, w, 5 * h, w, 2 * h, "Solo", texture);
        ajout_bouton_menu(*menu, w, 7 * h, w, 2 * h, "Multijoueur", texture);
        ajout_bouton_menu(*menu, w, 9 * h, w, 2 * h, "Option", texture);
        ajout_bouton_menu(*menu, w, 11 * h, w, 2 * h, "Quitter", texture);
    }else if(type == SOLO){
        (*menu)->tab_bouton = malloc(sizeof(t_bouton_menu));

        w = width / 3;
        h = height / 15;
        ajout_bouton_menu(*menu, w, 6 * h, w, 2 * h, "Nouvelle partie", texture);
        ajout_bouton_menu(*menu, w, 8 * h, w, 2 * h, "charger une partie", texture);
        ajout_bouton_menu(*menu, w, 10 * h, w, 2 * h, "Retour", texture);
    }else if(type == NOUVEAU_MENU){
        (*menu)->tab_bouton = NULL;
    }else{
        return INCORRECT_MENU_TYPE;
    }

    return OK;
}

/**
 * \fn t_erreur SDL_afficher_menu(t_menu * menu, SDL_Renderer * renderer)
 * \param
*/
t_erreur SDL_afficher_menu(t_menu * menu, SDL_Renderer * renderer){
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
    TTF_Font * police = TTF_OpenFont("/usr/share/fonts/truetype/Gargi/Gargi.ttf",40);
    SDL_Color couleur_texte = {0,0,0};
    SDL_Surface * texte;
    SDL_Texture * texte_tex;
    

    /* Affichage */
    int i;
    for(i = 0; i < menu->nb_bouton; i++){
        SDL_Rect r = {
            menu->tab_bouton[i]->x,
            menu->tab_bouton[i]->y,
            menu->tab_bouton[i]->width,
            menu->tab_bouton[i]->height
        };
        texte = TTF_RenderText_Blended(police, menu->tab_bouton[i]->titre, couleur_texte);
        texte_tex = SDL_CreateTextureFromSurface(renderer, texte);

        SDL_RenderCopy(renderer, menu->tab_bouton[i]->texture, NULL, &r);
        SDL_RenderCopy(renderer, texte_tex, NULL, &r);

        SDL_FreeSurface(texte);
        SDL_DestroyTexture(texte_tex);
    }
    TTF_CloseFont(police);
    return OK;
}

/**
 * \fn t_erreur detruire_bouton_menu(t_bouton_menu ** btn)
 * \param
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
 * \param
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
 * \fn t_erreur detruire_bouton_menu(t_bouton_menu ** btn)
 * \param
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
 * \param
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

t_erreur afficher_menu_test(t_menu * menu){
    int i;
    for(i = 0; i < menu->nb_bouton; i++){
        printf("x=%d, y=%d, w=%d, h=%d, titre=%s\n", menu->tab_bouton[i]->x, menu->tab_bouton[i]->y, menu->tab_bouton[i]->width, menu->tab_bouton[i]->height, menu->tab_bouton[i]->titre);
    }
    return OK;
}
#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <outils_SDL.h>
#include <entite.h>
#include <touches.h>
#include <fps.h>
#include <commun.h>
#include "entite_test.h"

int main (int argc, char ** argv, char ** env)
{
    pwd_init(argv[0],getenv("PWD"));
    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    int width = 1000;
    int height = 600;
    SDL_Window * pwindow = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/);
    SDL_GetWindowSize(pwindow, &width_window, &height_window);

    SDL_Renderer * renderer = SDL_CreateRenderer(pwindow,-1,SDL_RENDERER_ACCELERATED);

    /* Initialisation des sprites */
    Init_Sprite(renderer);

    /* Création de l'entité */
    t_entite * J = creer_entite_defaut(NULL,JOUEUR,22000,POSY_ENT_SCREEN,30);

    /******************************************************************************************/
    SDL_Rect mur_droit = {width_window-200,POSY_ENT_SCREEN+H_PART_SPRITE,200,200};
    SDL_Rect mur_gauche = {0,POSY_ENT_SCREEN+H_PART_SPRITE,200,200};
    SDL_Rect mur_haut = {0,0,width_window,100};
    SDL_Rect mur_bas = {0,POSY_ENT_SCREEN+H_PART_SPRITE,width_window,height_window - POSY_ENT_SCREEN - H_PART_SPRITE};

    char * chemin;
    creation_chemin("IMG/texture/pierre.png",&chemin);
    SDL_Texture *texture;
    Create_IMG_Texture(renderer, chemin, &texture);
    free(chemin);

    t_liste liste;
    init_liste(&liste);
    ajout_droit(&liste,&width);
    ajout_droit(&liste,&height);
    /******************************************************************************************/

    fps_init();
    double coef_fps = 1;
    uint8_t *ks;
    configTouches_t *ct;
    int continuer = 1;
    SDL_init_touches( &ks, &ct);
    while (continuer)
    {
        SDL_RenderClear(renderer);
        SDL_touches( ks, ct);

        /* Check si on doit quitter le programme */
        if (SDL_touche_appuyer( ks, QUITTER) || SDL_touche_appuyer( ks, ESCAPE))
        {
            continuer = 0;
            continue;
        }

        /**********************************************************************************/
        SDL_RenderCopy(renderer,texture,NULL,&mur_droit);
        SDL_RenderCopy(renderer,texture,NULL,&mur_haut);
        SDL_RenderCopy(renderer,texture,NULL,&mur_bas);
        SDL_RenderCopy(renderer,texture,NULL,&mur_gauche);
        /**********************************************************************************/
        
        Gestion_Entite(renderer,J,ks,coef_fps,collision,&liste);
        SDL_RenderPresent(renderer);
        coef_fps = fps();
    }

    SDL_exit_touches( &ks, &ct);

    detruire_entite(J);
    Quit_Sprite();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pwindow);
    IMG_Quit();
    SDL_Quit();
    pwd_quit();

    return 0;
}

int collision (SDL_Rect hit, t_collision_direction direction, t_liste * p)
{
    if (p)
    {
        int * param1, * param2;
        valeur_liste(p,0,(void **)&param1);
        valeur_liste(p,1,(void **)&param2);
        printf("width : %d / height : %d\n",*param1,*param2);
    }
    switch (direction)
    {
        case DIRECT_BAS_COLLI:
            if (hit.y < POSY_ENT_SCREEN) return POSY_ENT_SCREEN - hit.y;
            break;
    
        default:
            break;
    }
    return 0;
}
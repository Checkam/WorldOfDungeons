#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <outils_SDL.h>
#include <entite.h>

int main (int argc, char ** argv, char ** env)
{
    pwd_init(argv[0],getenv("PWD"));
    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    int width = 1000;
    int height = 600;
    SDL_Window * pwindow = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width, height, SDL_WINDOW_SHOWN);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(pwindow,-1,SDL_RENDERER_ACCELERATED);

    /* Création de la fenetre d'affichage du sprite */
    SDL_Rect fenetre = {0,0,width,height};

    /* Création de la texture du SPRITE */
    SDL_Texture * texture = Create_Sprite("IMG/texture/entite/joueur/sprite_apoil.png",renderer);

    /* Création de l'entité */
    t_entite * J = creer_entite_defaut(NULL,texture,JOUEUR);

    int i;
    for (i = 0; i < 20; i++)
    {
        SDL_RenderClear(renderer);
        Charger_Anima(renderer,fenetre,J,IMMOBILE);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pwindow);
    IMG_Quit();
    SDL_Quit();
    pwd_quit();

    return 0;
}
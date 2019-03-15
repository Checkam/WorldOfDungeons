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


    char * chemin;
    creation_chemin("IMG/texture/entite/joueur/sprite_apoil.png",&chemin);

    SDL_Texture * texture;
    Create_IMG_Texture(renderer,chemin,&texture);
    free(chemin);

    SDL_RenderClear(renderer);
    
    int w = 832/13;
    int h = 1344/21;

    SDL_Rect R2 = {0,0,width,height};
    SDL_Rect R = {0,11*h + 8,w,h};

    int i, j;
    for (i = 0, j = 0; i < 9 && j < 15; i++)
    {
        SDL_RenderClear(renderer);
        R.x = i*w;
        SDL_RenderCopy(renderer,texture,&R,&R2);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);

        if (i == 6){i = 0;j++;}
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pwindow);
    IMG_Quit();
    SDL_Quit();
    pwd_quit();

    return 0;
}
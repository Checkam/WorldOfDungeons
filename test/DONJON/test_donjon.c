/**
 * \file test_donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 24/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <commun.h>
#include <donjon.h>
#include <affichage.h>
#include <block.h>

#define NB_SALLE 20


int main(int argc, char **argv, char **env){

    if(argc != 2){
    	fprintf(stderr, "Usage:%s SEED\n", argv[0]);
        return EXIT_FAILURE;
    }

    SEED = atoi(argv[1]);

    /* Initialisation */
    pwd_init(argv[0], getenv("PWD"));

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == -1){
        printf("%s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width_window, height_window, SDL_WINDOW_SHOWN);
    if(screen == NULL){
        printf("%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Test de création, affichage + destruction du donjon */

    /* Création Donjon */
    t_liste *donjon = NULL;
    donjon_creer(&donjon, NB_SALLE);

    SDL_Rect pos_perso = {
        9 * width_window,
        10 * height_window + 7 * heightBrick,
        12,
        12
    };
   
    /* Affichage Donjon */
    SDL_RenderClear(renderer);

    donjon_afficher_SDL(renderer, donjon, pos_perso);
    donjon_afficher_Term(donjon, pos_perso);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    
    /* Destruction Donjon */
    donjon_detruire(&donjon);
    pwd_quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

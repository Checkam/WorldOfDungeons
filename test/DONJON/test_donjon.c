/**
 * \file test_donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 26/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <commun.h>
#include <donjon.h>
#include <affichage.h>
#include <block.h>
#include <entite.h>
#include <touches.h>
#include <time.h>
#include <fps.h>


#define NB_SALLE 20


int main(int argc, char **argv, char **env){

    if(argc != 2){
    	fprintf(stderr, "Usage:%s SEED\n", argv[0]);
        return EXIT_FAILURE;
    }

    fps_init();
    SEED = atoi(argv[1]);
    srand(time(NULL));
    /* Initialisation */
    pwd_init(argv[0], getenv("PWD"));

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == -1){
        fprintf(stderr, "%s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    if(TTF_Init() == -1){
        fprintf(stderr, "%s\n", TTF_GetError());
        return EXIT_FAILURE;
    }


    height_window = 630;
    width_window = 1040;
    width_block_sdl = width_window / NB_BLOCK_WIDTH;
    height_block_sdl = height_window / NB_BLOCK_HEIGHT;
    SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width_window, height_window, SDL_WINDOW_SHOWN);
    if(screen == NULL){
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Test de création, affichage + destruction du donjon */
    if(BLOCK_CreateTexture_sdl(renderer) != OK){
        erreur_save(VALUE_ERROR, NULL);
        return VALUE_ERROR;
    }

    uint8_t *ks;
    configTouches_t *ct;
    SDL_init_touches( &ks, &ct);

    Init_Sprite(renderer);
    t_entite * joueur = creer_entite_defaut("Joueur", JOUEUR, 9 * SIZE, 10 * MAX_SCREEN, 3 * height_block_sdl);
    Change_Damage_Entite(joueur, 25);
    Change_PV_Entite(joueur, 100, 100);

    /* Création Donjon */
    fprintf(stderr, "Test Création donjon ");
    t_donjon *donjon = NULL;
    if(donjon_creer(&donjon, NB_SALLE, joueur) == OK){
        fprintf(stderr, "--> OK\n");
    }else{
        fprintf(stderr, "--> KO\n");
    }

    double coef_fps;
    t_liste * fenetre = NULL;

    int continuer = 1;
    while(continuer){
        coef_fps = fps();
    /* Affichage Donjon */
        SDL_touches( ks, ct);
        SDL_RenderClear(renderer);
        
        donjon_afficher_SDL(renderer, donjon, joueur);
        donjon_gestion(renderer, donjon, joueur, ks, coef_fps);


        if ( SDL_touche_appuyer( ks, QUITTER) || SDL_touche_appuyer( ks, ESCAPE)) 
            continuer = 0;

        //donjon_afficher_Term(donjon, joueur);
        
        SDL_RenderPresent(renderer);
    }
    
    /* Destruction Donjon */
    fprintf(stderr, "Test destruction donjon ");
    if(donjon_detruire(&donjon) == OK){
        fprintf(stderr, "--> OK\n");
    }else{
        fprintf(stderr, "--> KO\n");
    }

    /* Libérationde la mémoire */
    BLOCK_DestroyTexture_sdl(renderer);
    SDL_exit_touches(&ks, &ct);
    Quit_Sprite();
    detruire_entite(joueur);
    pwd_quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

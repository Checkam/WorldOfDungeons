/**
 * \file test_menu.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Jasmin.
 * \date 13/03/2019
 * \version 2
*/

#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include <chemin.h>
#include <outils_SDL.h>

int main(int argc, char **argv, char **env)
{
    /* Initialisation */
    t_menu * menu = NULL;
    int width_window = 1000;
    int height_window = 600;
    pwd_init(argv[0], getenv("PWD"));

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if(TTF_Init() == -1){
        printf("%s\n", TTF_GetError());
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
    
    menu_init(renderer);


    /* Test création menu avec texture */
    printf("Test création Menu avec texture:\n");
    assert(menu_creer(PRINCIPAL, width_window, height_window, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu avec texture */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu avec texture:\n");
    assert(menu_afficher_SDL(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    /* Test destruction menu avec texture */
    printf("Test destruction Menu avec texture:\n");
    assert(menu_detruire(&menu) == OK);
    printf("\t-- OK\n");

    /* Test création menu sans texture */
    printf("Test Creation Menu sans texture:\n");
    assert(menu_creer(SOLO, width_window, height_window, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu sans texture */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu sans texture:\n");
    assert(menu_afficher_SDL(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    /* Test destruction menu sans texture */
    printf("Test destruction Menu sans texture:\n");
    assert(menu_detruire(&menu) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);

    /* Test création nouveau menu */
    printf("Test Creation nouveau Menu:\n");
    assert(menu_creer(NOUVEAU_MENU, width_window, height_window, &menu) == OK);
    printf("\t-- OK\n");
    printf("\tTest Ajout Bouton 1 Menu 3:\n");
    assert(menu_ajout_bouton(menu, 300, 300, 200, 50, "Bouton 1", true, MENU_NULL) == OK);
    printf("\t\t-- OK\n");
    printf("\tTest Ajout Bouton 2 Menu 3:\n");
    assert(menu_ajout_bouton(menu, 300, 360, 200, 50, "Bouton 2", true, MENU_NULL) == OK);
    printf("\t\t-- OK\n");
    
    /* Test affichage nouveau menu */
    SDL_RenderClear(renderer);
    printf("Test affichage nouveau Menu:\n");
    assert(menu_afficher_SDL(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    /* Test destruction nouveau menu */
    printf("Test destruction nouveau Menu:\n");
    assert(menu_detruire(&menu) == OK);
    printf("\t-- OK\n");

    /* Test gestion menu */
    menu_creer(PRINCIPAL, width_window, height_window, &menu);
    t_type_menu type_bouton;
    SDL_Event event;
    
    while(menu){
        SDL_RenderClear(renderer);
        SDL_PollEvent(&event);
        assert(menu_gestion_SDL(menu, event.button.x, event.button.y, event.button.state, &type_bouton) == OK);
        if(type_bouton != MENU_NULL){
            menu_suivant(&menu, type_bouton);
        }
        menu_afficher_SDL(menu, renderer);
        SDL_RenderPresent(renderer);
    }
    
    pwd_quit();
    menu_quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    TTF_Quit();
    SDL_Quit();
}

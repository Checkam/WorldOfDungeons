/**
 * \file test_erreur.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Tibane.
 * \date 07/03/2019
 * \version 0.1
*/

#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL_ttf.h>

int main()
{
    /* Initialisation */
    t_menu * menu = NULL;
    int width_window = 600;
    int height_window = 600;

    SDL_Init(SDL_INIT_EVERYTHING);

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
    SDL_Surface *surface_to_tex = NULL;
    surface_to_tex = SDL_LoadBMP("../../IMG/texture/herbe.bmp");
    SDL_Texture * fond = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
    SDL_FreeSurface(surface_to_tex);


    /* Test création menu 1 */
    printf("Test Creation Menu 1:\n");
    assert(creer_menu(PRINCIPAL, width_window, height_window, fond, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu 1 */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu 1:\n");
    assert(SDL_afficher_menu(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    /* Test destruction menu 1 */
    printf("Test destruction Menu 1:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    /* Test création menu 2 */
    printf("Test Creation Menu 2:\n");
    assert(creer_menu(SOLO, width_window, height_window, fond, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu 2 */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu 2:\n");
    assert(SDL_afficher_menu(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    /* Test destruction menu 2 */
    printf("Test destruction Menu 2:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);

    /* Test destruction menu 2 */
    printf("Test destruction Menu 2:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    /* Test création menu 3 */
    printf("Test Creation Menu 3:\n");
    assert(creer_menu(NOUVEAU_MENU, width_window, height_window, fond, &menu) == OK);
    printf("\t-- OK\n");
    printf("\tTest Ajout Bouton 1 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 300, 300, 200, 50, "Bouton 1", fond) == OK);
    printf("\t\t-- OK\n");
    printf("\tTest Ajout Bouton 2 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 300, 360, 200, 50, "Bouton 2", fond) == OK);
    printf("\t\t-- OK\n");
    
    /* Test affichage menu 3 */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu 3:\n");
    assert(SDL_afficher_menu(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    /* Test destruction menu 3 */
    printf("Test destruction Menu 3:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    
}


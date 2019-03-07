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

int main()
{
    t_menu * menu = NULL;
    int width_window = 600;
    int height_window = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width_window, height_window, SDL_WINDOW_SHOWN);
    SDL_Event event;
    if(screen == NULL){
        printf("%s\n", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("renderer NULL\n");
    }
    SDL_Surface *surface_to_tex = NULL;
    surface_to_tex = SDL_LoadBMP("../../IMG/texture/fond.bmp");
    SDL_Texture * fond = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
    SDL_FreeSurface(surface_to_tex);

    int repeat = 0;
    while (!repeat) {
   

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

    /* Test destruction menu 2 */
    printf("Test destruction Menu 2:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    /* Test destruction menu 2 */
    printf("Test destruction Menu 2:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    /* Test création menu 3 */
    printf("Test Creation Menu 3:\n");
    assert(creer_menu(NOUVEAU_MENU, width_window, height_window, fond, &menu) == OK);
    printf("\t-- OK\n");
    printf("\tTest Ajout Bouton 1 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 50, 60, 50, 10, "Bouton 1", fond) == OK);
    printf("\t\t-- OK\n");
    printf("\tTest Ajout Bouton 2 Menu 3:\n");
    assert(ajout_bouton_menu(menu, 50, 60, 50, 10, "Bouton 2", fond) == OK);
    printf("\t\t-- OK\n");
    
    /* Test affichage menu 3 */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu 3:\n");
    assert(SDL_afficher_menu(menu, renderer) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);

    /* Test destruction menu 3 */
    printf("Test destruction Menu 3:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");


        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    repeat = 1;
                    break;
            }
        }
        SDL_Delay(50);
    }
}

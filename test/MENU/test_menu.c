/**
 * \file test_menu.c
 * \brief Programme qui teste le module erreur.
 * \author GALBRUN Jasmin.
 * \date 10/03/2019
 * \version 1
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
    getpwd(argv[0], getenv("PWD"));

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
    
    char * chemin_img;
    creation_chemin("IMG/texture/herbe.bmp", &chemin_img);
    SDL_Texture * fond;
    Create_IMG_Texture(renderer, chemin_img, &fond);
    free(chemin_img);
    SDL_Color couleur_texte = {255,255,255};


    /* Test création menu 1 */
    printf("Test Creation Menu 1:\n");
    assert(creer_menu(PRINCIPAL, width_window, height_window, fond, &menu) == OK);
    printf("\t-- OK\n");

    /* Test affichage menu 1 */
    SDL_RenderClear(renderer);
    printf("Test affichage Menu 1:\n");
    assert(SDL_afficher_menu(menu, renderer, couleur_texte) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

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
    assert(SDL_afficher_menu(menu, renderer, couleur_texte) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    /* Test destruction menu 2 */
    printf("Test destruction Menu 2:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);

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
    assert(SDL_afficher_menu(menu, renderer, couleur_texte) == OK);
    printf("\t-- OK\n");
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    /* Test destruction menu 3 */
    printf("Test destruction Menu 3:\n");
    assert(detruire_menu(&menu) == OK);
    printf("\t-- OK\n");

    /* Test gestion menu */
    creer_menu(SOLO, width_window, height_window, fond, &menu);
    int repeat = 10000;
    int pos_btn_pressed;
    SDL_Event event;
    
    while(repeat){
        SDL_RenderClear(renderer);
        SDL_PollEvent(&event);
        assert(gestion_menu_SDL(menu, event.button, &pos_btn_pressed) == OK);
        if(pos_btn_pressed != -1){
            printf("--> %s\n", menu->tab_bouton[pos_btn_pressed]->titre);
        }
        SDL_afficher_menu(menu, renderer, couleur_texte);
        SDL_RenderPresent(renderer);
        repeat--;
    }
    detruire_menu(&menu);
    
    free(WOD_PWD);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    TTF_Quit();
    SDL_Quit();
}

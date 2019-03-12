#include "touches.h"

#include <SDL2/SDL.h>

#include <stdio.h>

int main () {
/* Ce main est le MINIMUM afin que le module touche fonctionne. SDL doit etre initialiser a la video au minimum.*/

    uint8_t *ks;
    configTouches_t *ct;
    int continuer = 1;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;

    window = SDL_CreateWindow("Appli test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_init_touches( &ks, &ct); /*doit etre appeler une seul fois pour initialiser le module*/

    while ( continuer ) {

        SDL_touches( ks, ct);

        if ( SDL_touche_appuyer( ks, QUITTER) ) /*permet de tester si une touche donner au second parametre est appuyer ou non ( voir dans /include/touches.h quelle touche sont disponible ) */
            continuer = 0;

        if ( SDL_touche_appuyer( ks, AVANCER) )
            printf("Avancer !\n");

	if ( SDL_touche_appuyer( ks, RECULER) )
            printf("Reculer !\n");

	if ( SDL_touche_appuyer( ks, DROITE) )
            printf("Droite !\n");

	if ( SDL_touche_appuyer( ks, GAUCHE) )
            printf("Gauche !\n");

        SDL_Delay(33);
    }

    SDL_exit_touches( &ks, &ct); /* doit etre appeler pour correctement fermer le module*/

    SDL_DestroyWindow(window);
}

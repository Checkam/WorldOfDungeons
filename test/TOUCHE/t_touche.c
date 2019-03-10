#include "touches.h"

#include <SDL2/SDL.h>

#include <stdio.h>

int main () {

    uint8_t *ks;
    configTouches_t *ct;
    int j = 0;

    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
        printf(" (%s)\n", SDL_GetError());

    SDL_Window *window;

    window = SDL_CreateWindow("Appli test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if ( !window )
        printf(" (%s)\n", SDL_GetError());

    SDL_init_touches( &ks, &ct);

    SDL_Delay(1500);

    while ( j < 20) {

        SDL_touches( ks, ct);

        if ( SDL_touche_appuyer( ks, QUITTER) )
            j = 20;

        if ( SDL_touche_appuyer( ks, AVANCER) )
            printf("Avancer !\n");
            
        j++;

        SDL_Delay(500);
    }

    SDL_exit_touches( &ks, &ct);

    SDL_DestroyWindow(window);
}
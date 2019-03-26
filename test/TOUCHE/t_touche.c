#include <touches.h>
#include <chemin.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module touche fonctionne. SDL doit etre initialiser a la video au minimum.*/

    uint8_t *ks;
    configTouches_t *ct;
    int continuer = 1;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;

    window = SDL_CreateWindow("Appli test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    pwd_init(argv[0],getenv("PWD")); /* doit etre exectuer AVANT SDL_init_touches */

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

        if ( SDL_touche_appuyer( ks, SPACE) )
                printf("Space !\n");

        if ( SDL_touche_appuyer( ks, SHIFT) )
                printf("Shift !\n");

        if ( SDL_touche_appuyer( ks, SOURIS_BTN_1) )
                printf("Souris btn 1 !\n");

        if ( SDL_touche_appuyer( ks, SOURIS_BTN_2) )
                printf("Souris btn 2 !\n");

        if ( SDL_touche_appuyer( ks, ESCAPE) )
                printf("Escape !\n");

        if ( SDL_wheel_state(ks) > 0 )
                printf("l'utilisateur a tourné sa molette vers le haut %d fois !\n", SDL_wheel_state(ks));
        else if ( SDL_wheel_state(ks) < 0 )
                printf("l'utilisateur a tourné sa molette vers le bas %d fois !\n", -SDL_wheel_state(ks)); /* remarque : le - permet d'afficher une valeur positive */
        
        SDL_reset_wheel_state(ks);

        SDL_Delay(100);
    }

    SDL_exit_touches( &ks, &ct); /* doit etre appeler pour correctement fermer le module*/

    SDL_DestroyWindow(window);

    pwd_quit(); /* doit etre execute APRES SDL_exit_touches */
}

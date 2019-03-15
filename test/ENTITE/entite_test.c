#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <outils_SDL.h>
#include <entite.h>
#include <touches.h>

int main (int argc, char ** argv, char ** env)
{
    pwd_init(argv[0],getenv("PWD"));
    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    int width = 1000;
    int height = 600;
    SDL_Window * pwindow = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width, height, SDL_WINDOW_SHOWN);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(pwindow,-1,SDL_RENDERER_ACCELERATED);

    /* Initialisation des sprites */
    Init_Sprite(renderer);

    /* Création de l'entité */
    t_entite * J = creer_entite_defaut(NULL,JOUEUR);

    /* Création de la fenetre d'affichage du sprite */
    SDL_Rect fenetre = {0,0,J->hitbox.w * 3,J->hitbox.h * 3};

    uint8_t *ks;
    configTouches_t *ct;
    int continuer = 1;
    SDL_init_touches( &ks, &ct);
    while (continuer)
    {
        SDL_touches( ks, ct);
        SDL_RenderClear(renderer);
        
        if (SDL_touche_appuyer( ks, QUITTER)) /*permet de tester si une touche donner au second parametre est appuyer ou non ( voir dans /include/touches.h quelle touche sont disponible ) */
            continuer = 0;

        else if (SDL_touche_appuyer( ks, AVANCER))
            Charger_Anima(renderer,fenetre,J,MARCHE_DEVANT);

	    else if (SDL_touche_appuyer( ks, RECULER))
            Charger_Anima(renderer,fenetre,J,MARCHE_DERRIERE);

	    else if (SDL_touche_appuyer( ks, DROITE))
            Charger_Anima(renderer,fenetre,J,MARCHE_DROITE);

	    else if (SDL_touche_appuyer( ks, GAUCHE))
            Charger_Anima(renderer,fenetre,J,MARCHE_GAUCHE);

        else Charger_Anima(renderer,fenetre,J,IMMOBILE);
        SDL_RenderPresent(renderer);
        //SDL_Delay(10);
    }

    SDL_exit_touches( &ks, &ct);

    Quit_Sprite();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pwindow);
    IMG_Quit();
    SDL_Quit();
    pwd_quit();

    return 0;
}
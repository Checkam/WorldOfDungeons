/**
 *
 *   \file main_test.c
 *   \brief Test du d'un main du programme
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 */

#include <SDL2/SDL.h>
#include <affichage.h>
#include <biome.h>
#include <block.h>
#include <commun.h>
#include <couleurs.h>
#include <generation.h>
#include <liste.h>
#include <math.h>
#include <outils_SDL.h>
#include <sauvegarde_map.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <touches.h>
#include <world_of_dungeons.h>

int main(int argc, char const *argv[]) {

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

  SDL_GetWindowSize(screen, &width_window, &height_window);

  SDL_Event event;

  SDL_Rect fondRect = {0, 0, width_window, height_window};

  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *fond;
  Create_IMG_Texture(renderer, "./IMG/texture/fond.bmp", &fond);

  BLOCK_CreateTexture_sdl(renderer);
  uint8_t *ks;
  configTouches_t *ct;

  SDL_init_touches(&ks, &ct);

  SEED = 898989;

  BIOME_init();

  t_block *tab;

  int i = 100;

  int taille = 0;

  t_liste list;
  init_liste(&list);

  int boucle = 1;

  while (boucle) {

    taille = AFF_GetMidHeight(&list);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    AFF_map_sdl(&list, renderer, 30);
    SDL_RenderPresent(renderer);

    SDL_touches(ks, ct);
    if (SDL_touche_appuyer(ks, QUITTER))
      boucle = 0;
    else if (SDL_touche_appuyer(ks, DROITE)) {
      i++;
      gen_col(&list, i, DROITE);
    } else if (SDL_touche_appuyer(ks, GAUCHE)) {
      i--;
      gen_col(&list, i - SIZE, GAUCHE);
    }
    SDL_Delay(1);
    //AFF_map_term(&list, 0, 400);
  }

  BIOME_Quit();
  SDL_exit_touches(&ks, &ct);
  BLOCK_DestroyTexture_sdl(renderer);
  detruire_liste(&list, free);
  SDL_DestroyTexture(fond);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();

  return 0;
}

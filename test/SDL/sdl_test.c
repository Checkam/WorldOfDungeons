/**
 *
 *   \file sdl_test.c
 *   \brief Test du module affichage et avec outils_SDL
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 */

#include <SDL2/SDL.h>
#include <affichage.h>
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
#include <world_of_dungeons.h>

static int Program = 1;

int main(int argc, char const *argv[]) {

  // ----------------------------------------------------------------- SDL

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *screen =
      SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window, SDL_WINDOW_SHOWN);

  SDL_Event event;

  SDL_Rect fondRect = {0, 0, width_window, height_window};

  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *fond;
  Create_IMG_Texture(renderer, "./IMG/texture/fond.bmp", &fond);

  SEED = 5454575;

  t_block *tab;

  int taille_max = 0;
  int i = 100;
  int repeat = 0;
  int taille = 0;

  t_liste list;
  init_liste(&list);

  int boucle = 100;

  while (boucle-- && Program && !repeat) {
    taille_max = gen_col(&tab, i);

    if (taille_liste(&list) > SIZE) {
      en_tete(&list);
      oter_elt(&list, free);
    }
    en_queue(&list);
    ajout_droit(&list, tab);

    taille = AFF_GetMidHeight(&list);
    if (taille == -1)
      taille = taille_max;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    AFF_map_sdl(&list, renderer, taille - 4);
    SDL_RenderPresent(renderer);

    while (SDL_PollEvent(&event))
      switch (event.type) {
      case SDL_QUIT:
        repeat = 1;
        break;
      }
    SDL_Delay(50);
    i++;
  }

  detruire_liste(&list, free);
  SDL_DestroyTexture(fond);
  SDL_DestroyRenderer(renderer);

  return 0;
}

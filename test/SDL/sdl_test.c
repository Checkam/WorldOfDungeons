/**
 *
 *   \file world_of_dungeons.c
 *   \brief Fichier main du projet World Of Dungeons
 *   \author {Maxence.D, Jasmin.G, Tibane.G, Mathieu.V}
 *   \version 0.1
 *   \date 30 Janvier 2019
 */

#include <SDL2/SDL.h>
#include <affichage.h>
#include <block.h>
#include <commun.h>
#include <couleurs.h>
#include <generation.h>
#include <liste.h>
#include <math.h>
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
  SDL_Window *screen = SDL_CreateWindow(
      "World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width_window, height_window, SDL_WINDOW_SHOWN);
  SDL_Event event;

  SDL_Rect fondRect = {0, 0, width_window, height_window};

  // SDL_Rect Rect = {200,height_window-100,0,0};

  SDL_Renderer *renderer =
      SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *fond = NULL;
  SDL_Texture *herbe_world = NULL;
  SDL_Texture *terre_world = NULL;
  SDL_Texture *eau_world = NULL;
  SDL_Texture *neige_world = NULL;
  SDL_Texture *tronc_world = NULL;
  SDL_Texture *feuille_world = NULL;
  SDL_Texture *roche_world = NULL;

  SDL_Surface *surface_to_tex = NULL;

  surface_to_tex = SDL_LoadBMP("./IMG/texture/fond.bmp");
  fond = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/herbe.bmp");
  herbe_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/terre.bmp");
  terre_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/eau.bmp");
  eau_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/neige.bmp");
  neige_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/tronc.bmp");
  tronc_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/feuille.bmp");
  feuille_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);
  SDL_FreeSurface(surface_to_tex);
  surface_to_tex = SDL_LoadBMP("./IMG/texture/neige.bmp");
  roche_world = SDL_CreateTextureFromSurface(renderer, surface_to_tex);

  SDL_FreeSurface(surface_to_tex);

  block_type_t blocks[NB_BLOCK] = {{AIR, "air", NULL},
                                   {HERBE, "herbe", herbe_world},
                                   {TERRE, "terre", terre_world},
                                   {EAU, "eau", eau_world},
                                   {SABLE, "sable", terre_world},
                                   {FEUILLE, "feuille", feuille_world},
                                   {BOIS, "bois", tronc_world},
                                   {ROCHE, "roche", roche_world},
                                   {NEIGE, "neige", neige_world},
                                   {GLACE, "glace", feuille_world}};

  block_type2_t blocks2[NB_BLOCK] = {
      {AIR, "air", NOIR},       {HERBE, "herbe", VERT},
      {TERRE, "terre", MARRON}, {EAU, "eau", BLEU},
      {SABLE, "sable", JAUNE},  {FEUILLE, "feuille", VERT},
      {BOIS, "bois", MARRON},   {ROCHE, "roche", GRIS},
      {NEIGE, "neige", BLANC},  {GLACE, "glace", CYAN}};

  SEED = 5454575;
  int DEPART = 100;
  int *tab;
  char chaine[50];
  sprintf(chaine, "map/map%d.txt", SEED);
  FILE *fichier = fopen(chaine, "w");
  int taille_max = 0;
  int i = DEPART;
  int repeat = 0;
  int taille = 0;

  t_liste list;
  init_liste(&list);

  while (1 && Program && !repeat) {
    taille_max = gen_col(&tab, i); /*Génère la nouvelle colonne*/

    if (taille_liste(&list) > SIZE) { /* INCOMPREHENSIBLE */
      en_tete(&list);
      oter_elt(&list, free);
    }
    en_queue(&list); /* PAREIL */
    ajout_droit(&list, tab);

    // save_tab(fichier, tab);
    // aff_map(&list,taille_max - 5, taille_max + 50, blocks2);
    // if(taille_max < HAUTEUR_EAU) taille_max = HAUTEUR_EAU;

    taille = taille_mid_aff(&list);
    if (taille == -1)
      taille = taille_max;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    aff_map_sdl(&list, renderer, blocks, taille - 4);
    SDL_RenderPresent(renderer);

    while (SDL_PollEvent(&event))
      switch (event.type) {
      case SDL_QUIT:
        repeat = 1;
        break;
      }
    SDL_Delay(50);

    // system("sleep 0.05");
    i++;
  }

  detruire_liste(&list, free);

  SDL_DestroyTexture(fond);
  SDL_DestroyTexture(herbe_world);
  SDL_DestroyTexture(terre_world);
  SDL_DestroyTexture(eau_world);
  SDL_DestroyTexture(neige_world);
  SDL_DestroyTexture(tronc_world);
  SDL_DestroyTexture(roche_world);
  SDL_DestroyTexture(feuille_world);

  SDL_DestroyRenderer(renderer);
  fclose(fichier);

  return 0;
}

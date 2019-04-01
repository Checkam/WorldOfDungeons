/**
 *
 *   \file main_test.c
 *   \brief Test du d'un main du programme
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <affichage.h>
#include <biome.h>
#include <block.h>
#include <chemin.h>
#include <commun.h>
#include <couleurs.h>
#include <entite.h>
#include <fps.h>
#include <generation.h>
#include <liste.h>
#include <map.h>
#include <math.h>
#include <menu.h>
#include <outils_SDL.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <touches.h>
#include <world_of_dungeons.h>

#define calY_aff (((map->joueur->hitbox.y - (map->joueur->hitbox.h / 2)) / height_block_sdl) - (MAX_SCREEN / 2))
#define calX_Debut ((map->joueur->hitbox.x) / width_block_sdl) - (SIZE / 2) - (map->joueur->hitbox.w / width_block_sdl)
#define calX_Fin ((map->joueur->hitbox.x) / width_block_sdl) + (SIZE / 2)

void test_souris(t_map *map, int *ks) {
  t_block *b;
  int x_mouse = 0, y_mouse = 0;
  if (SDL_touche_appuyer(ks, SOURIS_GAUCHE)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, (x_mouse / width_block_sdl) + calX_Debut + 2, MAX_SCREEN - (y_mouse / height_block_sdl) + calY_aff);

    if (b)
      b->id = AIR;
  }

  if (SDL_touche_appuyer(ks, SOURIS_DROIT)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, (x_mouse / width_block_sdl) + calX_Debut + 2, MAX_SCREEN - (y_mouse / height_block_sdl) + calY_aff);
    if (b)
      b->id = ROCHE;
  }
}

int main(int argc, char *argv[], char **env) {
  pwd_init(argv[0], getenv("PWD"));
  srand(time(NULL));
  SEED = 2312234;
  t_menu *menu = NULL;
  t_map *map = NULL;
  uint8_t *ks;
  configTouches_t *ct;
  width_block_sdl = 25;
  height_block_sdl = 25;

  //--------------------------------------------------------------------------------------------------------------
  // Initialisation SDL
  //--------------------------------------------------------------------------------------------------------------

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

  SDL_GetWindowSize(screen, &width_window, &height_window);

  SDL_Rect fondRect = {0, 0, width_window, height_window};
  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *fond;
  Create_IMG_Texture(renderer, "./IMG/texture/fond.bmp", &fond);
  BIOME_init();
  Init_Sprite(renderer);
  BLOCK_CreateTexture_sdl(renderer);
  menu_init(renderer);
  fps_init();
  SDL_init_touches(&ks, &ct);

  double coef_fps = 1;

  int boucle = 1;

  MAP_creer(&map, "World", 12281783);

  //----------------------------------------------------------------------------------------------------------------
  // Menu Début de jeux
  //----------------------------------------------------------------------------------------------------------------

  menu_creer(MENU_PRINCIPAL, width_window, height_window, &menu);
  t_type_menu type_bouton;

  while (menu) {
    SDL_RenderClear(renderer);
    SDL_touches(ks, ct);
    menu_gestion_SDL(menu, SDL_touche_appuyer(ks, SOURIS_GAUCHE), &type_bouton);
    if (type_bouton == MENU_QUITTER) {
      boucle = 0;
      menu_suivant(&menu, type_bouton);
    } else if (type_bouton != MENU_NULL) {
      menu_suivant(&menu, type_bouton);
    }
    menu_afficher_SDL(menu, renderer);
    SDL_RenderPresent(renderer);
  }

  //----------------------------------------------------------------------------------------------------------------
  // Boucle de jeux
  //----------------------------------------------------------------------------------------------------------------

  while (boucle) {
    SDL_touches(ks, ct);
    //QUITTER LE JEU
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE))
      boucle = 0;

    //GENERATION DROITE GAUCHE
    MAP_gen(map);

    //TEST SOURIS
    test_souris(map, ks);

    //Afficher le fond
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    //Affiche map
    MAP_afficher_sdl(map, renderer, calY_aff, calX_Debut, calX_Fin);
    //Affiche Joueur et
    Gestion_Entite(renderer, map->joueur, ks, coef_fps, map->list, GESTION_TOUCHES, ALL_ACTION, NULL);
    //Afficher le rendu final
    SDL_RenderPresent(renderer);

    coef_fps = fps();
  }

  //Quit du jeux
  MAP_sauvegarder(map);
  detruire_entite(map->joueur);
  Quit_Sprite();
  menu_quit();
  TTF_Quit();
  BIOME_Quit();
  MAP_detruction(&map);
  SDL_exit_touches(&ks, &ct);
  BLOCK_DestroyTexture_sdl(renderer);
  SDL_DestroyTexture(fond);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();
  pwd_quit();

  return 0;
}

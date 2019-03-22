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
#include <sauvegarde_map.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <touches.h>
#include <world_of_dungeons.h>

int collision(SDL_Rect hit, t_collision_direction direction) {
  switch (direction) {
  case DIRECT_BAS_COLLI:
    if (hit.y < 0)
      return 0 - hit.y;
    break;

  default:
    break;
  }
  return 1;
}

int main(int argc, char *argv[], char **env) {
  srand(time(NULL));
  SEED = rand() % 256;
  int i = rand() % 256;
  int taille = 30;
  t_menu *menu = NULL;

  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  SDL_Window *screen = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_window, height_window,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_GetWindowSize(screen, &width_window, &height_window);
  SDL_Rect fondRect = {0, 0, width_window, height_window};
  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture *fond;
  Create_IMG_Texture(renderer, "./IMG/texture/fond.bmp", &fond);
  BLOCK_CreateTexture_sdl(renderer);

  uint8_t *ks;
  configTouches_t *ct;

  pwd_init(argv[0], getenv("PWD"));
  SDL_init_touches(&ks, &ct);
  menu_init(renderer);
  TTF_Init();

  BIOME_init();

  Init_Sprite(renderer);
  fps_init();
  double coef_fps = 1;

  t_map *map = NULL;
  MAP_creer(&map, "World", 12281783);

  int boucle = 1;
  int x_mouse = 0, y_mouse = 0;

  while (taille_liste(map->list) <= SIZE) {
    i++;
    gen_col(map->list, i, DROITE);
  }
  taille = AFF_GetMidHeight(map->list) - 10;

  //----------------------------------------------------------------------------------------------------------------
  // Menu Début de jeux
  //----------------------------------------------------------------------------------------------------------------

  menu_creer(PRINCIPAL, width_window, height_window, &menu);
  t_type_menu type_bouton;
  SDL_Event event;

  t_entite *J = creer_entite_defaut(NULL, JOUEUR, (i * width_block_sdl), POSY_ENT_SCREEN);

  while (menu) {
    SDL_RenderClear(renderer);
    SDL_PollEvent(&event);
    menu_gestion_SDL(menu, event.button.state, &type_bouton);
    if (type_bouton != MENU_NULL) {
      menu_suivant(&menu, type_bouton);
    }
    menu_afficher_SDL(menu, renderer);
    SDL_RenderPresent(renderer);
  }

  //----------------------------------------------------------------------------------------------------------------
  // Boucle de jeux
  //----------------------------------------------------------------------------------------------------------------

  while (boucle) {

    // printf("x: %d hitbox.x: %d %d %d \n", i, (J->hitbox.x / width_block_sdl), (J->hitbox.x / width_block_sdl) + (SIZE / 2),
    //        (J->hitbox.x / width_block_sdl) - (SIZE / 2));

    taille = AFF_GetMidHeight(map->list);

    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    AFF_map_sdl(map->list, renderer, taille - (height_window / height_block_sdl / 2));
    Gestion_Entite(renderer, J, ks, coef_fps, collision);
    SDL_RenderPresent(renderer);

    SDL_touches(ks, ct);
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE)) {
      boucle = 0;
    }

    if (i + 1 == (J->hitbox.x / width_block_sdl)) {
      gen_col(map->list, (J->hitbox.x / width_block_sdl), DROITE);
      i++;
    }

    if (i - 1 == (J->hitbox.x / width_block_sdl)) {
      gen_col(map->list, (J->hitbox.x / width_block_sdl) - SIZE, GAUCHE);
      i--;
    }

    if (SDL_touche_appuyer(ks, SOURIS_GAUCHE)) {
      SDL_coord_souris(&x_mouse, &y_mouse);
      // Récuperation d'un block dans la liste
      t_block *b = MAP_GetBlockFromList(map, (x_mouse / width_block_sdl), MAX_SCREEN - (y_mouse / height_block_sdl) + taille + 1);

      if (b) {
        // printf("Block id: %d x:%d, y:%d x_mouse:%d y_mouse:%d\n", b->id, b->x, b->y, (x_mouse / width_block_sdl),
        //        MAX_SCREEN - (y_mouse / height_block_sdl) + taille + 1);
        b->id = 1;
      } else {
        printf("Block NULL\n");
      }
    }
    coef_fps = fps();
    //AFF_map_term(&list, 0, 400);
  }

  detruire_entite(J);
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

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

// int collision(SDL_Rect hit, t_collision_direction direction, t_liste *p) {
//   t_block *b;
//   t_map map;
//   map.list = p;
//
//   switch (direction) {
//   case DIRECT_BAS_COLLI:
//     b = MAP_GetBlock(&map, hit.x / width_block_sdl, hit.y / height_block_sdl);
//     //printf("%d %d\n", hit.x / width_block_sdl, hit.y / height_block_sdl);
//     if (b) {
//       // printf("b.x : %d b.y : %d hit.x %d hit.y %d\n", b->x, b->y, hit.x / width_block_sdl, hit.y / height_block_sdl);
//       return 25;
//     } else {
//       return 0;
//     }
//     break;
//   }
//
//   return 1;
// }

int main(int argc, char *argv[], char **env) {
  pwd_init(argv[0], getenv("PWD"));
  srand(time(NULL));
  SEED = rand() % 256;
  int i = rand() % 256;
  int taille = 30;
  t_menu *menu = NULL;
  t_map *map = NULL;
  uint8_t *ks;
  configTouches_t *ct;

  MAP_creer(&map, "World", 12281783);

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    printf("%s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (TTF_Init() == -1) {
    printf("%s\n", TTF_GetError());
    return EXIT_FAILURE;
  }

  if (IMG_Init(IMG_INIT_PNG) == -1) {
    printf("%s\n", TTF_GetError());
    return EXIT_FAILURE;
  }

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
  // GAME_init(renderer, &ks, &ct);

  double coef_fps = 1;

  int boucle = 1;
  int x_mouse = 0, y_mouse = 0;

  while (taille_liste(map->list) <= SIZE) {
    i++;
    gen_col(map->list, i, DROITE);
  }
  taille = AFF_GetMidHeight(map->list);

  //----------------------------------------------------------------------------------------------------------------
  // Menu Début de jeux
  //----------------------------------------------------------------------------------------------------------------

  menu_creer(MENU_PRINCIPAL, width_window, height_window, &menu);
  t_type_menu type_bouton;
  t_block *b = MAP_GetBlockFromList(map, SIZE / 2, AFF_GetMidHeight(map->list));
  t_entite *J = creer_entite_defaut(NULL, JOUEUR, b->x * width_block_sdl, b->y * height_block_sdl, 100);

  // while (menu) {
  //   SDL_RenderClear(renderer);
  //   SDL_touches(ks, ct);
  //   menu_gestion_SDL(menu, SDL_touche_appuyer(ks, SOURIS_GAUCHE), &type_bouton);
  //   if (type_bouton == MENU_QUITTER) {
  //     boucle = 0;
  //     menu_suivant(&menu, type_bouton);
  //   } else if (type_bouton != MENU_NULL) {
  //     menu_suivant(&menu, type_bouton);
  //   }
  //   menu_afficher_SDL(menu, renderer);
  //   SDL_RenderPresent(renderer);
  // }

  //----------------------------------------------------------------------------------------------------------------
  // Boucle de jeux
  //----------------------------------------------------------------------------------------------------------------

  while (boucle) {

    // printf("x: %d hitbox.x: %d %d %d \n", i, (J->hitbox.x / width_block_sdl), (J->hitbox.x / width_block_sdl) + (SIZE / 2),
    //        (J->hitbox.x / width_block_sdl) - (SIZE / 2));

    taille = AFF_GetMidHeight(map->list);
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    AFF_map_sdl(map->list, renderer, (J->hitbox.y / height_block_sdl) - MAX_SCREEN / 2);
    // printf("%d %d\n", J->hitbox.y, J->hitbox.y / height_block_sdl);

    Gestion_Entite(renderer, J, ks, coef_fps, collision, map->list);
    SDL_RenderPresent(renderer);

    SDL_touches(ks, ct);

    //QUITTER LE JEU
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE)) {
      boucle = 0;
    }

    t_block *b1 = NULL;
    //GENERATION DROITE GAUCHE
    if (i + 1 == (J->hitbox.x / width_block_sdl) + SIZE / 2) {
      gen_col(map->list, i, DROITE);
      i = (J->hitbox.x / width_block_sdl) + SIZE / 2;
      b1 = MAP_GetBlock(map, i, J->hitbox.y / height_block_sdl);
    }

    if (i - SIZE - 1 == (J->hitbox.x / width_block_sdl) - SIZE / 2) {
      gen_col(map->list, i - SIZE, GAUCHE);
      i = (J->hitbox.x / width_block_sdl) + SIZE / 2;
      b1 = MAP_GetBlock(map, i, J->hitbox.y / height_block_sdl);
    }

    printf("i : %d, i - SIZE : %d SIZE/2 : %d J.x : %d \n", i, i - SIZE, SIZE / 2, J->hitbox.x / width_block_sdl);

    // if (b1) {
    //   b1->id = 5;
    //   printf("id:%d x:%d y:%d\n", b1->id, b1->x, b1->y, taille);
    // } else {
    //   printf("Block NULL\n");
    // }

    //TEST SOURIS
    if (SDL_touche_appuyer(ks, SOURIS_GAUCHE)) {
      SDL_coord_souris(&x_mouse, &y_mouse);
      // Récuperation d'un block dans la liste
      t_block *b =
          MAP_GetBlockFromList(map, (x_mouse / width_block_sdl), MAX_SCREEN - (y_mouse / height_block_sdl) + (J->hitbox.y / height_block_sdl) + 1);

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

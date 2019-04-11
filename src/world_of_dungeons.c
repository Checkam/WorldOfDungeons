/**
 *
 *   \file main_test.c
 *   \brief Test du d'un main du programme
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 */
#define DEBUG
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
#include <inventaire.h>
#include <item.h>
#include <liste.h>
#include <map.h>
#include <math.h>
#include <menu.h>
#include <outils_SDL.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <structure_block.h>
#include <time.h>
#include <touches.h>
#include <world_of_dungeons.h>

#define calX_Souris(map, x_mouse) ((x_mouse / width_block_sdl) + ((map->joueur->hitbox.x) / width_block_sdl) - (SIZE / 2))
#define calY_Souris(map, y_mouse)                                                                                                                    \
  (MAX_SCREEN - (y_mouse / height_block_sdl) + (map->joueur->hitbox.y / height_block_sdl) - (POSY_ENT_SCREEN(map->joueur) / height_block_sdl) - 2)

void test_souris(t_map *map, uint8_t *ks, t_inventaire *inventaire, t_liste *liste) {
  t_block *b;
  int x_mouse = 0, y_mouse = 0;
  if (SDL_touche_appuyer(ks, SOURIS_GAUCHE)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, calX_Souris(map, x_mouse), calY_Souris(map, y_mouse));

    if (b && b->id != AIR && abs(b->x - ((map->joueur->hitbox.x) / width_block_sdl)) < 3 &&
        abs(b->y - ((map->joueur->hitbox.y) / height_block_sdl)) < 3) {
      casser_block((t_materiaux)b->id, &liste);
      ajout_item_dans_inventaire(inventaire, liste);
      b->id = AIR;
      // fprintf(stderr, "%d %d %d %d\n", calY_aff(map), (POSY_ENT_SCREEN(map->joueur) / height_block_sdl), map->joueur->hitbox.y, b->y);
    }
  }

  if (SDL_touche_appuyer(ks, SOURIS_DROIT)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, calX_Souris(map, x_mouse), calY_Souris(map, y_mouse));
    if (b && b->id == AIR && abs(b->x - ((map->joueur->hitbox.x) / width_block_sdl)) < 3 &&
        abs(b->y - ((map->joueur->hitbox.y) / height_block_sdl)) < 3) {
      b->id = ROCHE;
    }
  }
}

int main(int argc, char *argv[], char **env) {
  pwd_init(argv[0], getenv("PWD"));
  srand(time(NULL));
  SEED = 233242;
  t_menu *menu = NULL;
  t_map *map = NULL;

  uint8_t *ks;
  configTouches_t *ct;
  width_block_sdl = 25;
  height_block_sdl = 25;
  height_window = 600;
  width_window = 1000;

  WIDTH = width_window;
  HEIGHT = height_window;
  scaleW = DEFAULT_SIZE_SCREEN_W / WIDTH;
  scaleH = DEFAULT_SIZE_SCREEN_H / HEIGHT;
  uiScale = 100;

  //--------------------------------------------------------------------------------------------------------------
  // Initialisation SDL
  //--------------------------------------------------------------------------------------------------------------

#include <game_init.h>

  t_inventaire *inventaire = create_inventaire();
  alloc_item(inventaire, 12);

  t_liste *liste = malloc(sizeof(t_liste));
  init_liste(liste);
  en_tete(liste);

  double coef_fps = 1;

  int boucle = 1;

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
    } else if (type_bouton == MENU_NOUVELLE_PARTIE) {

      MAP_creer(&map, "World", 12281783);
      menu_suivant(&menu, type_bouton);
    } else if (type_bouton == MENU_CHARGER_PARTIE) {

      MAP_charger(&map, "World");
      menu_suivant(&menu, type_bouton);
    } else if (type_bouton != MENU_NULL) {
      menu_suivant(&menu, type_bouton);
    }
    menu_afficher_SDL(menu, renderer);
    SDL_RenderPresent(renderer);

    coef_fps = fps();
  }

  inventaire_changer_constante(9);
  //----------------------------------------------------------------------------------------------------------------
  // Boucle de jeux
  //----------------------------------------------------------------------------------------------------------------

  while (boucle) {
    SDL_reset_wheel_state(ks);
    SDL_touches(ks, ct);
    //QUITTER LE JEU
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE))
      boucle = 0;

    //GENERATION DROITE GAUCHE
    MAP_gen(map);

    //TEST SOURIS
    test_souris(map, ks, inventaire, liste);

    //Afficher le fond
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    //Affiche map
    MAP_afficher_sdl(map, renderer); //Modifier l'affichage de la map pour afficher des demi colone
    //Affiche Joueur et
    Gestion_Entite(renderer, map->joueur, ks, coef_fps, map->list, GESTION_TOUCHES, ALL_ACTION, NULL, CENTER_SCREEN);

    //Affichage Inventaire
    if (SDL_touche_appuyer(ks, X)) {
      inventaire_afficher(renderer, inventaire);
    } else {
      SDL_afficher_barre_action(renderer, inventaire, SDL_wheel_state(ks));
    }
    //Afficher le rendu final
    SDL_RenderPresent(renderer);

    coef_fps = fps();
  }

//Quit du jeux
#include <game_quit.h>

  return 0;
}

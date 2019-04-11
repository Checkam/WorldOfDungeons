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
#include <string.h>
#include <structure_block.h>
#include <time.h>
#include <touches.h>
#include <world_of_dungeons.h>

#define calY_aff(map)                                                                                                                                \
  (map->joueur->hitbox.y / height_block_sdl) - (POSY_ENT_SCREEN(map->joueur) / height_block_sdl) - 2 // Le moins 2 a trouver d'ou il vient

#define calX_Debut(map) ((map->joueur->hitbox.x - map->joueur->hitbox.w / 2) / width_block_sdl) - (SIZE / 2)

#define calX_Fin(map) ((map->joueur->hitbox.x + map->joueur->hitbox.w / 2) / width_block_sdl) + (SIZE / 2)

void test_souris(t_map *map, uint8_t *ks, t_inventaire *inventaire, t_liste *liste) {
  t_block *b;
  int x_mouse = 0, y_mouse = 0;
  if (SDL_touche_appuyer(ks, SOURIS_GAUCHE)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, (x_mouse / width_block_sdl) + calX_Debut(map) + 1, MAX_SCREEN - (y_mouse / height_block_sdl) + calY_aff(map));

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
    b = MAP_GetBlock(map, (x_mouse / width_block_sdl) + calX_Debut(map) + 1, MAX_SCREEN - (y_mouse / height_block_sdl) + calY_aff(map));
    if (b && b->id == AIR && abs(b->x - ((map->joueur->hitbox.x) / width_block_sdl)) < 3 &&
        abs(b->y - ((map->joueur->hitbox.y) / height_block_sdl)) < 3) {
      b->id = ROCHE;
    }
  }
}

char *InputText(SDL_Renderer *renderer, char *titre) {
  char *chemin_police;
  creation_chemin("data/police/8-BIT_WONDER.ttf", &chemin_police);

  char *text = malloc(sizeof(char) * 100);
  strcpy(text, "\0");
  int done = 0;

  SDL_Texture *fond;
  Create_IMG_Texture(renderer, "./IMG/texture/menu/fond_text.png", &fond);
  SDL_Color couleur = {255, 255, 255};

  SDL_Rect posText = {width_window / 2, height_window / 2 - 15, 30, 30};
  SDL_Rect posTitre = {width_window / 2 - (strlen(titre) * 25), height_window / 2 - 150, 50 * strlen(titre), 50};
  SDL_Rect fondRect = {0, 0, width_window, height_window};
  SDL_Texture *text_texture;

  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, fond, NULL, &fondRect);

  Create_Text_Texture(renderer, titre, chemin_police, 14, couleur, BLENDED, &text_texture);
  SDL_RenderCopy(renderer, text_texture, NULL, &posTitre);

  SDL_RenderPresent(renderer);
  SDL_StartTextInput();
  while ((!done && strlen(text) < 100) || (strlen(text) == 0)) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_TEXTINPUT:
        strcat(text, event.text.text);
        posText.w += 30;
        posText.x -= 15;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
          if (strlen(text) > 0) {
            text[strlen(text) - 1] = '\0';
            posText.w -= 30;
            posText.x += 15;
          }
        } else if (event.key.keysym.sym == SDLK_RETURN) {
          if (strlen(text) > 0) {
            done = 1;
          }
        }
      }
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, fond, NULL, &fondRect);
      if (strlen(text) > 0) {
        Create_Text_Texture(renderer, text, chemin_police, 20, couleur, BLENDED, &text_texture);
        SDL_RenderCopy(renderer, text_texture, NULL, &posText);
      }
      Create_Text_Texture(renderer, titre, chemin_police, 14, couleur, BLENDED, &text_texture);
      SDL_RenderCopy(renderer, text_texture, NULL, &posTitre);

      SDL_RenderPresent(renderer);
    }
  }
  free(chemin_police);
  return text;
}

int main(int argc, char *argv[], char **env) {
  pwd_init(argv[0], getenv("PWD"));
  srand(time(NULL));
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

      char *nom_map = InputText(renderer, "Nom de la map");
      MAP_creer(&map, nom_map, rand());
      free(nom_map);

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

    //GENERATION DROITE GAUCHE
    MAP_gen(map);

    //TEST SOURIS
    test_souris(map, ks, inventaire, liste);

    //Afficher le fond
    SDL_RenderCopy(renderer, fond, NULL, &fondRect);

    //Affiche map
    MAP_afficher_sdl(map, renderer, calY_aff(map), calX_Debut(map), calX_Fin(map)); //Modifier l'affichage de la map pour afficher des demi colone
    //Affiche Joueur et
    Gestion_Entite(renderer, map->joueur, ks, coef_fps, map->list, GESTION_TOUCHES, ALL_ACTION, NULL, CENTER_SCREEN);

    //Affichage Inventaire
    //QUITTER LE JEU
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE))
      boucle = 0;
    else if (SDL_touche_appuyer(ks, G)) {

      SDL_SetWindowFullscreen(screen, SDL_WINDOW_FULLSCREEN_DESKTOP);
      SDL_GetWindowSize(screen, &width_window, &height_window);
      WIDTH = width_window;
      HEIGHT = height_window;
      scaleW = DEFAULT_SIZE_SCREEN_W / WIDTH;
      scaleH = DEFAULT_SIZE_SCREEN_H / HEIGHT;
      fondRect.w = width_window;
      fondRect.h = height_window;

    } else if (SDL_touche_appuyer(ks, X)) {
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

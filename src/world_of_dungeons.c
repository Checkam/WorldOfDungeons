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

    //CASSER UN BLOCK
    if (b && BLOCK_estCassable(b->id) && abs(b->x - ((map->joueur->hitbox.x) / width_block_sdl)) < 3 &&
        abs(b->y - ((map->joueur->hitbox.y) / height_block_sdl)) <= 3) {
      casser_block((t_materiaux)b->id, &liste);
      ajout_item_dans_inventaire(inventaire, liste);
      b->id = AIR;
      b->plan = ARRIERE_PLAN;
    }
  }

  //POSER UN BLOCK
  if (SDL_touche_appuyer(ks, SOURIS_DROIT)) {
    SDL_coord_souris(&x_mouse, &y_mouse);
    // Récuperation d'un block dans la liste
    b = MAP_GetBlock(map, calX_Souris(map, x_mouse), calY_Souris(map, y_mouse));
    if (b && b->id == AIR && abs(b->x - ((map->joueur->hitbox.x) / width_block_sdl)) < 3 &&
        abs(b->y - ((map->joueur->hitbox.y) / height_block_sdl)) <= 3) {
      b->id = ROCHE;
      b->plan = PREMIER_PLAN;
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

void startPlayMap(t_map *map, SDL_Renderer *renderer) {
  int boucle = 1;
  uint8_t *ks;
  configTouches_t *ct;
  int coef_fps = 1;
  SDL_init_touches(&ks, &ct);
  inventaire_init(renderer);
  t_inventaire *inventaire = create_inventaire();
  alloc_item(inventaire, 20);
  inventaire_changer_constante(9);
  t_liste *liste = malloc(sizeof(t_liste));
  init_liste(liste);
  en_tete(liste);

  SDL_Rect fondRect = {0, 0, width_window, height_window};
  SDL_Texture *ciel;
  Create_IMG_Texture(renderer, "./IMG/texture/environnement/ciel.png", &ciel);

  SDL_Texture *sous_terre;
  Create_IMG_Texture(renderer, "./IMG/texture/environnement/grotte.png", &sous_terre);

  while (boucle) {
    SDL_reset_wheel_state(ks);
    SDL_touches(ks, ct);

    //GENERATION DROITE GAUCHE
    MAP_gen(map);

    //TEST SOURIS
    test_souris(map, ks, inventaire, liste);

    //Afficher le fond
    if (map->joueur->hitbox.y / height_block_sdl > HAUTEUR_MINIMUN)
      SDL_RenderCopy(renderer, ciel, NULL, &fondRect);
    else
      SDL_RenderCopy(renderer, sous_terre, NULL, &fondRect);

    //Affiche map
    MAP_afficher_sdl(map, renderer); //Modifier l'affichage de la map pour afficher des demi colone
    //Affiche Joueur et
    Gestion_Entite(renderer, map->joueur, ks, coef_fps, map->list, GESTION_TOUCHES, ALL_ACTION, NULL, CENTER_SCREEN);

    //Affichage Inventaire
    //QUITTER LE JEU
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE)) {
      boucle = 0;
    } else if (SDL_touche_appuyer(ks, X)) {
      inventaire_afficher(renderer, inventaire);
    } else {
      SDL_afficher_barre_action(renderer, inventaire, SDL_wheel_state(ks));
    }
    //Afficher le rendu final
    SDL_RenderPresent(renderer);

    coef_fps = fps();
  }
  printf("Nb col : %d\n", taille_liste(map->list));
  MAP_sauvegarder(map);
  free_inventaire(inventaire);
  detruire_liste(liste, free);
  free(liste);
  SDL_DestroyTexture(ciel);
  SDL_DestroyTexture(sous_terre);
  SDL_exit_touches(&ks, &ct);
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

  double coef_fps = 1;

  int game = 1;

  //----------------------------------------------------------------------------------------------------------------
  // Menu Début de jeux
  //----------------------------------------------------------------------------------------------------------------

  while (game) {
    menu_creer(MENU_PRINCIPAL, width_window, height_window, &menu);
    t_type_menu type_bouton;
    while (menu) {
      SDL_RenderClear(renderer);
      SDL_touches(ks, ct);
      menu_gestion_SDL(menu, SDL_touche_appuyer(ks, SOURIS_GAUCHE), &type_bouton);
      if (type_bouton == MENU_QUITTER) {
        game = 0;
        menu_suivant(&menu, type_bouton);
      } else if (type_bouton == MENU_NOUVELLE_PARTIE) {

        char *nom_map = InputText(renderer, "Nom de la map");
        MAP_creer(&map, nom_map, rand());
        free(nom_map);

        menu_suivant(&menu, type_bouton);

        if (map) {

          startPlayMap(map, renderer);
          MAP_detruction(&map);
        } else {

          char *chemin_police;
          creation_chemin("data/police/8-BIT_WONDER.ttf", &chemin_police);
          SDL_Texture *fond;
          Create_IMG_Texture(renderer, "./IMG/texture/menu/fond_text.png", &fond);

          SDL_Color couleur = {255, 255, 255};
          char *titre = "ERREUR MAP";
          SDL_Rect posTitre = {width_window / 2 - (strlen(titre) * 25), height_window / 2, 50 * strlen(titre), 50};

          SDL_Texture *text_texture;
          SDL_RenderClear(renderer);
          Create_Text_Texture(renderer, titre, chemin_police, 20, couleur, BLENDED, &text_texture);
          SDL_RenderCopy(renderer, text_texture, NULL, &posTitre);

          SDL_RenderPresent(renderer);
          while (!SDL_touche_appuyer(ks, QUITTER) && !SDL_touche_appuyer(ks, ESCAPE))
            SDL_touches(ks, ct);
        }

      } else if (type_bouton == MENU_CHARGER_PARTIE) {

        MAP_lister();

        char *nom_map = InputText(renderer, "Nom de la map");
        MAP_charger(&map, nom_map);
        free(nom_map);

        menu_suivant(&menu, type_bouton);

        if (map) {
          startPlayMap(map, renderer);
          MAP_detruction(&map);
        } else {

          char *chemin_police;
          creation_chemin("data/police/8-BIT_WONDER.ttf", &chemin_police);

          SDL_Texture *fond;
          Create_IMG_Texture(renderer, "./IMG/texture/menu/fond_text.png", &fond);
          SDL_Color couleur = {255, 255, 255};
          char *titre = "ERREUR MAP";
          SDL_Rect posTitre = {width_window / 2 - (strlen(titre) * 25), height_window / 2, 50 * strlen(titre), 50};

          SDL_Texture *text_texture;
          SDL_RenderClear(renderer);
          Create_Text_Texture(renderer, titre, chemin_police, 20, couleur, BLENDED, &text_texture);
          SDL_RenderCopy(renderer, text_texture, NULL, &posTitre);

          SDL_RenderPresent(renderer);
          while (!SDL_touche_appuyer(ks, QUITTER) && !SDL_touche_appuyer(ks, ESCAPE))
            SDL_touches(ks, ct);
        }
      } else if (type_bouton != MENU_NULL) {
        menu_suivant(&menu, type_bouton);
      }
      menu_afficher_SDL(menu, renderer);
      SDL_RenderPresent(renderer);

      coef_fps = fps();
    }

    //----------------------------------------------------------------------------------------------------------------
    // Boucle de jeux
    //----------------------------------------------------------------------------------------------------------------
  }

//Quit du jeux
#include <game_quit.h>

  return 0;
}

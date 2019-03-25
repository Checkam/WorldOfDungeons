#include "entite_test.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chemin.h>
#include <commun.h>
#include <entite.h>
#include <fps.h>
#include <liste.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <touches.h>

int main(int argc, char **argv, char **env) {
  pwd_init(argv[0], getenv("PWD"));
  SDL_Init(SDL_INIT_EVERYTHING);

  IMG_Init(IMG_INIT_PNG);

  int width = 1000;
  int height = 600;
  SDL_Window *pwindow = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                         SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/);
  SDL_GetWindowSize(pwindow, &width_window, &height_window);

  SDL_Renderer *renderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

  /* Initialisation des sprites */
  Init_Sprite(renderer);

  /* Création de l'entité */
  t_entite *J = creer_entite_defaut(NULL, JOUEUR, 22000, POSY_ENT_SCREEN, 40);

  /******************************************************************************************/
  SDL_Rect mur_droit = {width_window - 200, POSY_ENT_SCREEN + H_PART_SPRITE, 200, 200};
  SDL_Rect mur_gauche = {0, POSY_ENT_SCREEN + H_PART_SPRITE, 200, 200};
  SDL_Rect mur_haut = {0, 0, width_window, 100};
  SDL_Rect mur_bas = {0, POSY_ENT_SCREEN + H_PART_SPRITE, width_window, height_window - POSY_ENT_SCREEN - H_PART_SPRITE};

  char *chemin;
  creation_chemin("IMG/texture/pierre.png", &chemin);
  SDL_Texture *texture;
  Create_IMG_Texture(renderer, chemin, &texture);
  free(chemin);

  t_liste l1, l2;
  init_liste(&l1);
  init_liste(&l2);
  int a = 5, b = 6;
  ajout_droit(&l1, &a);
  ajout_droit(&l1, &l2);
  ajout_droit(&l2, &b);
  /******************************************************************************************/

  fps_init();
  double coef_fps = 1;
  uint8_t *ks;
  configTouches_t *ct;
  int continuer = 1;
  SDL_init_touches(&ks, &ct);
  while (continuer) {
    SDL_RenderClear(renderer);
    SDL_touches(ks, ct);

    /* Check si on doit quitter le programme */
    if (SDL_touche_appuyer(ks, QUITTER) || SDL_touche_appuyer(ks, ESCAPE)) {
      continuer = 0;
      continue;
    }

    /**********************************************************************************/
    SDL_RenderCopy(renderer, texture, NULL, &mur_droit);
    SDL_RenderCopy(renderer, texture, NULL, &mur_haut);
    SDL_RenderCopy(renderer, texture, NULL, &mur_bas);
    SDL_RenderCopy(renderer, texture, NULL, &mur_gauche);
    /**********************************************************************************/

    Gestion_Entite(renderer, J, ks, coef_fps, &l1);
    SDL_RenderPresent(renderer);
    coef_fps = fps();
  }

  SDL_exit_touches(&ks, &ct);

  detruire_entite(J);
  Quit_Sprite();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(pwindow);
  IMG_Quit();
  SDL_Quit();
  pwd_quit();

  return 0;
}

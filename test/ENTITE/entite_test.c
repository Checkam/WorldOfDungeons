#include "entite_test.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <chemin.h>
#include <commun.h>
#include <entite.h>
#include <fps.h>
#include <liste.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <touches.h>
#include <time.h>

int main(int argc, char **argv, char **env) {
  srand(time(NULL));
  pwd_init(argv[0], getenv("PWD"));
  SDL_Init(SDL_INIT_EVERYTHING);

  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  int width = 1000;
  int height = 600;
  width_block_sdl = width / NB_BLOCK_WIDTH;
  height_block_sdl = height / NB_BLOCK_HEIGHT;
  SDL_Window *pwindow = SDL_CreateWindow("World Of Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                         SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/);
  SDL_GetWindowSize(pwindow, &width_window, &height_window);

  SDL_Renderer *renderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

  /* Initialisation des sprites */
  Init_Sprite(renderer);

  /* Création de l'entité */
  t_entite *J = Load_Entite("test/ENTITE/","save_ent");
  if (!J)
  {
    J = creer_entite_defaut(NULL, JOUEUR, 22000, 15, 60);
    Change_Mana_Entite(J,200,250);
    Change_PV_Entite(J,2000,2000);
    Change_Name_Entite(J,"ziharccos");
  }

  /* Création entité 2 */
  t_entite *Mob = Load_Entite("test/ENTITE/","save_mob");
  if (!Mob)
  {
    Mob = creer_entite_defaut("Maxence",ZOMBIE,22005,16,70);
  }

  /* Création Liste d'entité */
  t_liste * liste = Create_Liste_Entite(21950,22050,25,ZOMBIE,5,70);

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

    Gestion_Entite(renderer, J, ks, coef_fps, NULL,GESTION_TOUCHES,ALL_ACTION,NULL,CENTER_SCREEN);
    //fprintf(stderr,"Joueur : %d\n", J->hitbox.y);

    update_posY_entite(Mob,coef_fps,NULL,NOT_CENTER_SCREEN);
    // Gestion_Entite(renderer,Mob,ks,coef_fps,NULL,GESTION_ACTION,MARCHE_DEVANT,J);
    // Gestion_Entite(renderer,Mob,ks,coef_fps,NULL,GESTION_ACTION,ACCELERER,J);
    Gestion_Entite(renderer,Mob,ks,coef_fps,NULL,GESTION_ACTION,ATTAQUE_DROITE,J,NOT_CENTER_SCREEN);
    
    update_posY_liste_entite(liste,coef_fps,NULL,NOT_CENTER_SCREEN);
    Print_Liste_Entite_Screen(renderer,J,liste,IMMOBILE,NOT_CENTER_SCREEN);

    SDL_RenderPresent(renderer);
    coef_fps = fps();
    Add_PV_Entite(J,-4);
    // fprintf(stderr,"Mob : Y -> %d\n",Mob->hitbox.y);
    // fprintf(stderr,"Joueur : Y -> %d\n",J->hitbox.y);
  }
  //Save_Entite(J,"test/ENTITE/","save_ent");
  //Save_Entite(Mob,"test/ENTITE/","save_mob");

  SDL_exit_touches(&ks, &ct);

  detruire_entite(J);
  detruire_entite(Mob);
  Destroy_Liste_Entite(&liste);
  Quit_Sprite();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(pwindow);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  pwd_quit();

  return 0;
}

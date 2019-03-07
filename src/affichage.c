/**
*   \file affichage.c
*   \brief Fonction d'affichage de liste de block
*   \author {Maxence.D}
*   \version 0.1 
*   \date 28 fevrier 2019 
**/
#include <SDL2/SDL.h>
#include <block.h>
#include <commun.h>
#include <couleurs.h>
#include <liste.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * \fn int dansFenetre(SDL_Rect r)
 * \brief 
 * \param
 * \return 
**/
int dansFenetre(SDL_Rect r) {
  return (r.x < width_window && r.x >= 0 && r.y >= 0 && r.y < height_window);

}

/**
 * \fn char *CouleurBlock(int id, block_type2_t blocks[]) 
 * \brief 
 * \param
 * \return 
**/
char *CouleurBlock(int id, block_type2_t blocks[]) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id)
      return blocks[i].texture;
  return NOIR;
}

/**
 * \fn SDL_Texture *TextureBlock(int id, block_type_t blocks[])
 * \brief 
 * \param
 * \return 
**/
SDL_Texture *TextureBlock(int id, block_type_t blocks[]) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id)
      return blocks[i].texture;
  return NULL;
}

/**
 * \fn int taille_mid_aff()
 * \brief 
 * \param
 * \return 
**/
int taille_mid_aff() {
  int *tab;
  int i = 0;
  int taille = MAX - 1;
  if (taille_liste() > SIZE) { /* INCOMPREHENSIBLE */
    for (en_tete(); !hors_liste(); suivant(), i++) {
      valeur_elt(&tab);
      if (i == (SIZE / 2)) {
        while (tab[taille] != HERBE && tab[taille] != NEIGE &&
               tab[taille] != EAU) {
          taille--;
        }
        return taille;
      }
    }
  }
  return -1;
}

/**
 * \fn void aff_map_sdl(SDL_Renderer *renderer, block_type_t blocks[], int min)
 * \brief 
 * \param
 * \return 
**/
void aff_map_sdl(SDL_Renderer *renderer, block_type_t blocks[], int min) {
  int i, j = 0;
  int *map; /*Tableau de recupèration de la liste*/
  SDL_Rect r = {0, 0, 0, 0};
  if (min)
    for (j = 0, en_tete(); !hors_liste(); suivant()) {
      valeur_elt(&map);
      for (i = MAX_SCREEN; i > 0; i--) {
        r.x = (j * (width_window / SIZE));
        r.y = (height_window - (i * (height_window / MAX_SCREEN)));
        r.h = 50;
        r.w = 50;
        if (dansFenetre(r))
          SDL_RenderCopy(renderer, TextureBlock(*(map + i + min), blocks), NULL,
                         &r);

        // printf("x:%d y:%d\n",r.x,r.y);
        // printf("%d\n",i);
      }
      j++;
    }
}

/**
 * \fn void aff_map(int min, int max, block_type2_t blocks[])
 * \brief 
 * \param
 * \return 
**/
void aff_map(int min, int max, block_type2_t blocks[]) {
  system("clear");
  int i;
  int *map; // Tableau de recupèration de la liste
  for (i = MAX_SCREEN - 1; i >= 0; i--) {
    for (en_tete(); !hors_liste(); suivant()) {
      valeur_elt(&map);
      printf("%s %s", CouleurBlock(*(map + i), blocks), NOIR);
    }
    printf("\n");
  }
}

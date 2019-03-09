/**
 *   \file affichage.c
 *   \brief Fonction d'affichage de liste de block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 9 mars 2019
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
 * \brief Vérifie si les coordonées d'un carré (SDL_rect) est dans la fenetre
 * \param r un carré SDL
 * \return un int 1 si dans la fenetre sinon 0
 **/
int dansFenetre(SDL_Rect r) {
  return (r.x < width_window && r.x >= 0 && r.y >= 0 && r.y < height_window);
}

/**
 \fn char *CouleurBlock(int id, block_type2_t blocks[])
 \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 \param id C'est le chiffre qui represente la texture rechercher
 \param blocks un tableau de block
 \return la texture (une char * pour le terminal)
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
 * \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 * \param id C'est le chiffre qui represente la texture rechercher
 * \param blocks un tableau de block
 * \return la texture (une char * pour le terminal)
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
 * \brief Récupère la hauteur du milieu de la liste
 * \param list La liste des tableaux de block
 * \return return la hauteur du milieu d'affichage
 **/
int taille_mid_aff(t_liste *list) {
  int *tab;
  int i = 0;
  int taille = MAX - 1;
  if (taille_liste(list) > SIZE) { /* INCOMPREHENSIBLE */
    for (en_tete(list); !hors_liste(list); suivant(list), i++) {
      valeur_elt(list, (void **)&tab);
      if (i == (SIZE / 2)) {
        while (tab[taille] != HERBE && tab[taille] != NEIGE && tab[taille] != EAU) {
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
 * \brief Affiche une liste de tableau de block en SDL
 * \param list La liste de tableau de blocks a afficher
 * \param renderer Le rendu SDL
 * \param blocks Un tableau de blocks
 * \param min le minimun de l'affichage (exemple: )
 * \return Retourne rien
 **/
void aff_map_sdl(t_liste *list, SDL_Renderer *renderer, block_type_t blocks[], int min) {
  int i, j = 0;
  int *map; /*Tableau de recupèration de la liste*/
  SDL_Rect r = {0, 0, 0, 0};
  if (min)
    for (j = 0, en_tete(list); !hors_liste(list); suivant(list)) {
      valeur_elt(list, (void **)&map);
      for (i = MAX_SCREEN; i > 0; i--) {
        r.x = (j * (width_window / SIZE));
        r.y = (height_window - (i * (height_window / MAX_SCREEN)));
        r.h = 50;
        r.w = 50;
        if (dansFenetre(r))
          SDL_RenderCopy(renderer, TextureBlock(*(map + i + min), blocks), NULL, &r);
      }
      j++;
    }
}

/**
 * \fn void aff_map(int min, int max, block_type2_t blocks[])
 * \brief Affiche une liste de tableau de block sur le terminal
 * \param list La liste de tableau de blocks a afficher
 * \param min le minimun de l'affichage
 * \param max le max de l'affichage
 * \param blocks Un tableau de blocks
 * \return Retourne rien
 **/
void aff_map(t_liste *list, int min, int max, block_type2_t blocks[]) {
  system("clear");
  int i;
  int *map; // Tableau de recupèration de la liste
  for (i = MAX_SCREEN - 1; i >= 0; i--) {
    for (en_tete(list); !hors_liste(list); suivant(list)) {
      valeur_elt(list, (void **)&map);
      printf("%s %s", CouleurBlock(*(map + i), blocks), NOIR);
    }
    printf("\n");
  }
}

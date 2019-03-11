/**
 *   \file affichage.c
 *   \brief Fonction d'affichage de liste de block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/

#include <SDL2/SDL.h>
#include <block.h>
#include <commun.h>
#include <couleurs.h>
#include <liste.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \fn int AFF_RectInWindow(SDL_Rect r)
 * \brief Vérifie si les coordonées d'un carré (SDL_rect) est dans la fenetre
 * \param r un carré SDL
 * \return un int 1 si dans la fenetre sinon 0
 **/
int AFF_RectInWindow(SDL_Rect r) { return (r.x < width_window && r.x >= 0 && r.y >= 0 && r.y < height_window); }

//FONCTION PROVISOIR POUR L'AFFICHAGE
/**
 * \fn int AFF_GetMidHeight(t_liste *list)
 * \brief Récupère la hauteur du milieu de la liste
 * \param list La liste des tableaux de block
 * \return return la hauteur du milieu d'affichage
 **/
int AFF_GetMidHeight(t_liste *list) {
  t_block *tab;
  int i = 0;
  int taille = MAX - 1;
  if (taille_liste(list) > SIZE) {
    for (en_tete(list); !hors_liste(list); suivant(list), i++) {
      valeur_elt(list, (void **)&tab);
      if (i == (SIZE / 2)) {
        while (tab[taille].id != HERBE && tab[taille].id != NEIGE && tab[taille].id != EAU && tab[taille].id != SABLE && tab[taille].id != GLACE) {
          taille--;
        }
        return taille;
      }
    }
  }
  return -1;
}

/**
 * \fn void AFF_map_sdl(t_liste *list, SDL_Renderer *renderer, int min)
 * \brief Affiche une liste de tableau de block en SDL
 * \param list La liste de tableau de blocks a afficher
 * \param renderer Le rendu SDL
 * \param min le minimun de l'affichage (exemple: )
 * \return Retourne rien
 **/
void AFF_map_sdl(t_liste *list, SDL_Renderer *renderer, int min) {
  int i, j = 0;
  t_block *map; /*Tableau de recupèration de la liste*/
  SDL_Rect r = {0, 0, 0, 0};
  if (min)
    for (j = 0, en_tete(list); !hors_liste(list); suivant(list)) {
      valeur_elt(list, (void **)&map);
      for (i = MAX_SCREEN; i > 0; i--) {
        r.x = (j * (width_window / SIZE));
        r.y = (height_window - (i * (height_window / MAX_SCREEN)));
        r.h = 25;
        r.w = 25;
        if (i + min < MAX && i + min > 0) {
          if (AFF_RectInWindow(r)) {
            SDL_Texture *texture_block = BLOCK_GetTexture_sdl(map[i + min].id);
            SDL_RenderCopy(renderer, texture_block, NULL, &r);
          }
        } else {
          SDL_RenderCopy(renderer, NULL, NULL, &r);
        }
      }
      j++;
    }
}

/**
 * \fn void AFF_map_term(t_liste *list, int min, int max)
 * \brief Affiche une liste de tableau de block sur le terminal
 * \param list La liste de tableau de blocks a afficher
 * \param min le minimun de l'affichage
 * \param max le max de l'affichage
 * \return Retourne rien
 **/
void AFF_map_term(t_liste *list, int min, int max) {
  int i;
  t_block *map; // Tableau de recupèration de la liste
  for (i = MAX_SCREEN - 1; i >= 0; i--) {
    for (en_tete(list); !hors_liste(list); suivant(list)) {
      valeur_elt(list, (void **)&map);
      printf("%s %s", BLOCK_GetTexture_term(map[i].id), NOIR);
    }
    printf("\n");
  }
  printf("\e[0m");
}

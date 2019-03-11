/**
*   \file generation.c
*   \brief Fonction de génération procédural grace a Perlin Noise
*   \author {Maxence.D}
*   \version 0.1
*   \date 10 mars 2019
*
*   \fn void init_map(t_block *map)
*   \brief Initialise un tableau de block
*
*   \fn int gen_col(t_block **tab, int x)
*   \brief Génere une colone de block
*
**/

#include <biome.h>
#include <block.h>
#include <commun.h>
#include <couleurs.h>
#include <generation.h>
#include <math.h>
#include <perlin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structure_block.h>

void changeBiome(int x, int y) {
  if (x % W_BIOME == SEED % W_BIOME) {
    biome = (int)((double)x * perlin2d(x - 1, y, FREQ, DEPTH) * (double)HAUTEUR_SURFACE + 1) % NB_BIOME;
  }
}

void init_map(t_block *map) {
  int i;
  for (i = 0; i < MAX; i++) {
    map[i].id = AIR;
  }
}

// Initialise un tableau de n valeur a 0
void initTab(int tab[], int n) {
  for (int i = 0; i < n; i++)
    tab[i] = 0;
}

//FONCTION QUI CALCUL LES PROCHAINES HAUTEUR (A REFAIRE)
int PreviewHeight(int x, int P_Height[], int nb) {
  int taille_max = 0;
  for (int i = 0; i < nb; i++) {
    taille_max = perlin2d(x + i, MAX, FREQ, DEPTH) * MAX;
    P_Height[i] = taille_max;
  }
  return 1;
}

int gen_col(t_block **tab, int x) {
  int rnd, j;
  int taille_max = perlin2d(x, MAX, FREQ, DEPTH) * MAX;
  *tab = malloc(sizeof(t_block) * MAX);
  init_map(*tab);
  changeBiome(x, taille_max);

  STRUCT_generation(x, *tab, taille_max);

  /* génération eau */
  for (j = 0; taille_max + j < HAUTEUR_EAU; j++) {
    if (j + taille_max == HAUTEUR_EAU - 1 && (biome == TOUNDRA || biome == TAIGA)) {
      (*tab)[taille_max + j].id = GLACE;
      (*tab)[taille_max + j].y = taille_max + j;
      (*tab)[taille_max + j].x = x;
    } else if ((*tab)[taille_max + j].id == AIR) {
      (*tab)[taille_max + j].id = EAU;
      (*tab)[taille_max + j].y = taille_max + j;
      (*tab)[taille_max + j].x = x;
    }
  }

  /* génération herbe + sable + terre */
  for (j = 1; j <= HAUTEUR_SURFACE; j++) {
    if (((*tab)[taille_max].id == EAU || (*tab)[taille_max].id == GLACE) && j == 1) {
      (*tab)[taille_max - j].id = SABLE;
      (*tab)[taille_max - j].y = taille_max - j;
      (*tab)[taille_max - j].x = x;
    } else if (j == 1) {
      if (biome == PRAIRIES || biome == FORET) {
        (*tab)[taille_max - j].id = HERBE;
        (*tab)[taille_max - j].y = taille_max - j;
        (*tab)[taille_max - j].x = x;
      } else if (biome == TOUNDRA || biome == TAIGA) {
        (*tab)[taille_max - j].id = NEIGE;
        (*tab)[taille_max - j].y = taille_max - j;
        (*tab)[taille_max - j].x = x;
      } else if (biome == DESERTS) {
        (*tab)[taille_max - j].id = SABLE;
        (*tab)[taille_max - j].y = taille_max - j;
        (*tab)[taille_max - j].x = x;
      }
    } else {
      (*tab)[taille_max - j].id = TERRE;
      (*tab)[taille_max - j].y = taille_max - j;
      (*tab)[taille_max - j].x = x;
    }
  }

  (*tab)[taille_max - HAUTEUR_SURFACE].id = GRAVIER;

  /* Génération profondeur */
  for (j = 0; j < taille_max - HAUTEUR_SURFACE; j++) {
    rnd = perlin2d(x, j, FREQ, DEPTH) * MAX;

    if (taille_max - j > PROFONDEUR_GROTTE && j >= BEDROCK && rnd >= (MAX / 2 - SIZE_GROTTE) && rnd <= (MAX / 2 + SIZE_GROTTE)) { /* grotte */
      (*tab)[j].id = AIR;
      (*tab)[j].y = j;
      (*tab)[j].x = x;
    } else {
      (*tab)[j].id = ROCHE;
      (*tab)[j].y = j;
      (*tab)[j].x = x;
    }
  }
  return taille_max;
}

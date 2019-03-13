/**
 *   \file structure_block.c
 *   \brief Module de gestion des structure_block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 13 mars 2019
 **/
#include <biome.h>
#include <block.h>
#include <commun.h>
#include <generation.h>
#include <perlin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structure_block.h>

int STRUCT_GetWidth(t_struct_block *struct_block, t_struct_block_type type) {
  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (struct_block[i].type == type)
      return struct_block[i].largeur;
  }
  return 0;
}

char *STRUCT_GetPath(t_struct_block *struct_block, t_struct_block_type type) {
  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (struct_block[i].type == type)
      return struct_block[i].path;
  }
  return 0;
}

/**
 * \fn void STRUCT_generation(int x, t_block map[MAX], int y)
 * \brief Permet de generer les structures block
 * \param x le x de generation
 * \param map le tableau de block ou ajouter la structure
 * \param y hauteur du tableau actuel
**/
void STRUCT_generation(int x, t_block map[MAX], int y) {
  static int struct_spawn = 0;
  static int new_struct = 0;
  static t_struct_block_type type_spawn;
  static t_struct_block_type type_can_spawn[NB_STRUCT_BLOCK];
  int nb_can_spawn = 0;
  int pourcent = 0;
  int struct_random = 0;

  t_struct_block struct_block[NB_STRUCT_BLOCK] = {{ARBRE_TAIGA, 7, "structure/arbre_taiga", 30, (biome == TAIGA)},
                                                  {ARBRE_FORET, 7, "structure/arbre_foret", 80, (biome == FORET)},
                                                  {GRAND_ARBRE_FORET, 7, "structure/arbre_foret2", 10, (biome == FORET)},
                                                  {BUISSON, 8, "structure/buisson", 60, (biome == FORET)},
                                                  {CACTUS, 3, "structure/cactus", 30, (biome == DESERTS)}};

  if (struct_spawn) { // Permet de prendre la ligne du block a test
    char line[50];
    FILE *file = NULL;
    file = fopen(STRUCT_GetPath(struct_block, type_spawn), "r");

    if (file != NULL) {
      for (int j = 0; j < struct_spawn; j++) {
        for (int l = 0; l < 50; l++)
          line[l] = 0;
        fgets(line, 50, file);
      }

      for (int j = 0; j < strlen(line) && (j + y < MAX - 1); j++)
        map[y + j].id = line[j] - '0';

      fclose(file);
    }
    struct_spawn--;
  } else if (!struct_spawn && new_struct > 0) { //Attente avant une nouvelle ligne
    new_struct--;
  }

  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (nb_can_spawn < NB_STRUCT_BLOCK && !new_struct && struct_block[i].condition && y > HAUTEUR_EAU) {
      pourcent = ((int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * 1232321) % 100) + 1;
      if (pourcent < struct_block[i].pourcent_spawn) {
        type_can_spawn[nb_can_spawn] = struct_block[i].type;
        nb_can_spawn++;
      }
    }
  }
  if (!struct_spawn && !new_struct && nb_can_spawn > 0) {
    new_struct = (int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * (double)W_BIOME + 1) % DIST_MAX_STRUCT;
    struct_random = (int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * (double)W_BIOME + 1) % nb_can_spawn;
    type_spawn = type_can_spawn[struct_random];
    struct_spawn = STRUCT_GetWidth(struct_block, type_spawn);
  }
}

/**
 *   \file structure_block.c
 *   \brief Module de gestion des structure_block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 11 mars 2019
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

void STRUCT_generation(int x, t_block map[MAX], int y) {
  static int struct_spawn = 0;
  static int new_struct = 0;
  static t_struct_block_type type_spawn;

  t_struct_block struct_block[NB_STRUCT_BLOCK] = {{ARBRE_TAIGA, 7, "structure/arbre/arbre_taiga", 30, (biome == TAIGA)},
                                                  {ARBRE_FORET, 7, "structure/arbre/arbre_foret", 30, (biome == FORET)},
                                                  {BUISSON, 4, "structure/arbre/buisson", 30, (biome == FORET)},
                                                  {CACTUS, 3, "structure/arbre/cactus", 30, (biome == DESERTS)}};

  for (int i = 0; i < NB_STRUCT_BLOCK; i++)
    if (!struct_spawn && !new_struct && struct_block[i].condition && y > HAUTEUR_EAU) {
      struct_spawn = struct_block[i].largeur;
      new_struct = (int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * (double)W_BIOME + 1) % DIST_MAX_TREE;
      type_spawn = struct_block[i].type;
    } else if (struct_spawn && type_spawn == struct_block[i].type) {
      char line[50];
      FILE *file = NULL;
      file = fopen(struct_block[i].path, "r");

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
    } else if (!struct_spawn && new_struct > 0 && type_spawn == struct_block[i].type) {
      new_struct--;
    }
}

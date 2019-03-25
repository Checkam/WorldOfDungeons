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

t_struct_block struct_block[NB_STRUCT_BLOCK] = {{ARBRE_TAIGA, 7, "structure/arbre_taiga", 30, TAIGA},
                                                {ARBRE_FORET, 7, "structure/arbre_foret", 80, FORET},
                                                {GRAND_ARBRE_FORET, 7, "structure/arbre_foret2", 10, FORET},
                                                {BUISSON, 5, "structure/buisson", 60, FORET},
                                                {CACTUS, 3, "structure/cactus", 30, DESERTS}};

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

int STRUCT_CanSpawn(int x, int i) { return 0; }

/**
 * \fn void STRUCT_generation(int x, t_block map[MAX], int y)
 * \brief Permet de generer les structures block
 * \param x le x de generation
 * \param map le tableau de block ou ajouter la structure
 * \param y hauteur du tableau actuel
**/
void STRUCT_generation(int x, int y, int dir, t_block map[MAX]) {
  y++;
  srand(x);
  static int struct_spawn;
  static int new_struct;
  static t_struct_block_type type_spawn;
  static int last_dir;
  int struct_random = 0;

  if (last_dir != dir) {
    struct_spawn = 0;
    new_struct = 0;
    last_dir = dir;
  }

  if (struct_spawn <= 0 && x % 50 == 0) {
    struct_random = rand() % NB_STRUCT_BLOCK;
    type_spawn = struct_block[struct_random].type;
    struct_spawn = struct_block[struct_random].largeur;
    printf("x: %d\n", x);
  }

  if (struct_spawn) { // Permet de prendre la ligne du block a test

    char line[50];
    FILE *file = NULL;
    file = fopen(STRUCT_GetPath(struct_block, type_spawn), "r");

    if (file != NULL) {
      for (int j = 0; j < (struct_spawn / 2) + 1; j++) {
        for (int l = 0; l < 50; l++)
          line[l] = 0;
        fgets(line, 50, file);
      }

      for (int j = 0; j < strlen(line) && (j + y < MAX - 1); j++)
        map[y + j].id = line[j] - '0';

      fclose(file);
    }
    struct_spawn--;
    printf("struct_spawn : %d type_spawn : %d struct_random: %d\n", struct_spawn, type_spawn, struct_random);
  }
}

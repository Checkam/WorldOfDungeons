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
#include <map.h>
#include <perlin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structure_block.h>
#include <touches.h>

t_struct_block struct_block[NB_STRUCT_BLOCK] = {{ARBRE_TAIGA, 7, "structure/arbre_taiga", 30, TAIGA},
                                                {ARBRE_FORET, 7, "structure/arbre_foret", 80, FORET},
                                                {GRAND_ARBRE_FORET, 7, "structure/arbre_foret2", 10, FORET},
                                                {BUISSON, 5, "structure/buisson", 60, FORET},
                                                {CACTUS, 3, "structure/cactus", 30, DESERTS},
                                                {ENTRE_DONJON, 5, "structure/donjon", 1, FORET}

};

int STRUCT_GetWidth(t_struct_block_type type) {
  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (struct_block[i].type == type)
      return struct_block[i].largeur;
  }
  return 0;
}

char *STRUCT_GetPath(t_struct_block_type type) {
  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (struct_block[i].type == type)
      return struct_block[i].path;
  }
  return 0;
}

int STRUCT_CanSpawn(int x, int i) { return 0; }

int STRUCT_Spawn(int x, int y, t_struct_block_type type_spawn, t_map *map) {
  t_block *tab;
  x -= STRUCT_GetWidth(type_spawn) / 2;
  for (int i = 0; i <= STRUCT_GetWidth(type_spawn); i++) {
    tab = MAP_GetColX(map, x + i);
    STRUCT_SetCol(i, y, type_spawn, tab);
  }
  return 0;
}

#define LECTURE 100

int STRUCT_SetCol(int x_struct, int y, t_struct_block_type type_spawn, t_block *tab) {
  if (!tab)
    return -1;

  char line[LECTURE];
  FILE *file = NULL;
  file = fopen(STRUCT_GetPath(type_spawn), "r");

  if (file != NULL) {
    for (int j = 0; j < x_struct; j++) {
      for (int l = 0; l < LECTURE; l++)
        line[l] = 0;
      fgets(line, LECTURE, file);
    }
    int var = 0, j = 0;
    char line_temp[LECTURE];
    while (sscanf(line, "%d:%s", &var, line_temp) == 2) {
      tab[y + j].id = var;
      strcpy(line, line_temp);
      j++;
      // printf("%s\n", line);
    }
    // printf("\n");
    fclose(file);
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
void STRUCT_generation(int x, int y, int dir, t_block tab[MAX]) {
  y++;
  static int struct_spawn = 0, new_struct = 0, struct_spawn_dir1, new_struct_dir1;
  static t_struct_block_type type_spawn;
  static t_struct_block_type type_can_spawn[NB_STRUCT_BLOCK];
  static int last_dir;

  int nb_can_spawn = 0;
  int struct_random = 0;

  if (last_dir != dir) {
    struct_spawn_dir1 ^= struct_spawn ^= struct_spawn_dir1 ^= struct_spawn;
    new_struct_dir1 ^= new_struct ^= new_struct_dir1 ^= new_struct;

    last_dir = dir;
  }

  if (dir == DROITE) {
    x += 3;
  } else if (dir == GAUCHE) {
    x -= 3;
  }

  if (struct_spawn) { // Permet de prendre la ligne du block a test
    STRUCT_SetCol(struct_spawn, y, type_spawn, tab);
    struct_spawn--;
  } else if (!struct_spawn && new_struct > 0) { //Attente avant une nouvelle ligne
    new_struct--;
  }

  for (int i = 0; i < NB_STRUCT_BLOCK; i++) {
    if (nb_can_spawn < NB_STRUCT_BLOCK && !new_struct && struct_block[i].biome == biome) {
      type_can_spawn[nb_can_spawn] = struct_block[i].type;
      nb_can_spawn++;
    }
  }

  if (!struct_spawn && !new_struct && nb_can_spawn > 0) {
    new_struct = (int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * (double)W_BIOME + 1) % DIST_MAX_STRUCT;
    struct_random = (int)((double)x * perlin2d(x, MAX, FREQ, DEPTH) * (double)W_BIOME + 1) % nb_can_spawn;
    type_spawn = type_can_spawn[struct_random];
    struct_spawn = STRUCT_GetWidth(type_spawn);
  }
}

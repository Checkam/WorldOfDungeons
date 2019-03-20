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


int spawn_for_biome(t_struct_block *struct_block,t_struct_block_type *spawn_biome){
  int j;
  for(int i=0, j=0;i < NB_STRUCT_BLOCK;i++){
    if(struct_block[i].biome == biome){
      spawn_biome[j++] = struct_block[i].type;
    } 
  }
  return j;
}

/**
 * \fn void STRUCT_generation(int x, t_block map[MAX], int y)
 * \brief Permet de generer les structures block
 * \param x le x de generation
 * \param map le tableau de block ou ajouter la structure
 * \param y hauteur du tableau actuel
**/
void STRUCT_generation(int x, t_block map[MAX], int y) {
  y++;
  static int struct_spawn = 0;
  static int new_struct = 0;

  static t_struct_block_type spawn_biome[NB_STRUCT_BLOCK];
  static t_struct_block_type type_spawn;


  t_struct_block struct_block[NB_STRUCT_BLOCK] = {{ARBRE_TAIGA, 7, "structure/arbre_taiga", 30, TAIGA},
                                                  {ARBRE_FORET, 7, "structure/arbre_foret", 80,  FORET},
                                                  {GRAND_ARBRE_FORET, 7, "structure/arbre_foret2", 10, FORET},
                                                  {BUISSON, 8, "structure/buisson", 60, FORET},
                                                  {CACTUS, 3, "structure/cactus", 30, DESERTS}};

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

  if (!struct_spawn && !new_struct) {
    
    new_struct = (int)((double)x * perlin2d(x, x, FREQ, DEPTH) * (double)W_BIOME + 1) % DIST_MAX_STRUCT;

    int nb_biome = spawn_for_biome(struct_block,spawn_biome);

    type_spawn = spawn_biome[((int)((double)x * perlin2d(x, x, FREQ, DEPTH) * (double)W_BIOME + 1) % nb_biome)];
    
    struct_spawn = STRUCT_GetWidth(struct_block, type_spawn);
  }
}




/**
 *   \file structure_block.h
 *   \brief Module de gestion des structure_block
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 11 mars 2019
 **/

#ifndef __STRUCTURE_BLOCK_H__
#define __STRUCTURE_BLOCK_H__

#include <commun.h>
#include <block.h>
#include <biome.h>
#include <map.h>

#define NB_STRUCT_BLOCK 6

#define DIST_MAX_STRUCT 15

typedef enum {
  ARBRE_TAIGA = 0,
  ARBRE_FORET = 1,
  CACTUS = 2,
  BUISSON = 3,
  GRAND_ARBRE_FORET = 4,
  ENTRE_DONJON = 5
} t_struct_block_type;

typedef struct {
   t_struct_block_type type;
   int largeur;
   char * path;
   int pourcent_spawn;
   int biome;
} t_struct_block;

void STRUCT_generation(int x, int y, int dir,t_block map[MAX] );
int STRUCT_SetCol(int x_struct, int y, t_struct_block_type type_spawn, t_block tab[MAX]);
int STRUCT_Spawn(int x, int y, t_struct_block_type type_spawn, t_map *map);
#endif

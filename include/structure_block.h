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

#define NB_STRUCT_BLOCK 5

#define DIST_MAX_STRUCT 15

typedef enum {
  ARBRE_TAIGA,
  ARBRE_FORET,
  CACTUS,
  BUISSON,
  GRAND_ARBRE_FORET
} t_struct_block_type;

typedef struct {
   t_struct_block_type type;
   int largeur;
   char * path;
   int pourcent_spawn;
   int condition;
} t_struct_block;

void STRUCT_generation(int x, int y, int dir,t_block map[MAX] );

#endif

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

#define NB_STRUCT_BLOCK 5

#define HAUTEUR_ARBRE 5
#define FREQ_ARBRE HAUTEUR_ARBRE - 3
#define H_MIN_GEN_ARBRE HAUTEUR_EAU + 10
#define H_MAX_GEN_ARBRE 100
#define DIST_MAX_TREE 10

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

void STRUCT_generation(int x, t_block map[MAX], int y);

#endif

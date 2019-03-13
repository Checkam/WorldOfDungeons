/**
 *   \file biome.h
 *   \brief Module de gestion de biome
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 13 mars 2019
 **/
#ifndef __BIOME_H__
#define __BIOME_H__

#include <commun.h>
#include <block.h>
#include <liste.h>

#define W_BIOME 200
#define NB_BIOME 5

/**
 * \enum t_biome_type
 * \brief Enumeration de type de biome
**/
typedef enum {
       FORET= 0,
       PRAIRIES,
       TAIGA,
       TOUNDRA,
       DESERTS
} t_biome_type;


t_biome_type biome;

typedef struct {
  t_block_type block_type;
  int hauteur_max,hauteur_min;
} t_layer;

typedef struct {
  t_biome_type type;
  t_liste *layers; //liste de layer
  int nb_layers;
} t_biome;







#endif

void changeBiome(int x, int y);
void BIOME_init();
t_biome *BIOME_CreateBiome(t_biome_type type);
void BIOME_AddLayer(t_biome *b, t_block_type block_type, int min, int max);

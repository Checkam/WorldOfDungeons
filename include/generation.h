/**
 *   \file generation.h
 *   \brief Module de generation de la map
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 13 mars 2019
 **/
#ifndef __GENERATION_H__
#define __GENERATION_H__

#include <block.h>

#define HAUTEUR_SURFACE 4
#define PROFONDEUR_GROTTE 15
#define BEDROCK 3
#define SIZE_GROTTE 3
#define HAUTEUR_EAU MAX / 2.5


#endif
/* Generation d'un colone grace a la coordonné en abcisse */
int gen_col(t_block **tab, int x);
void init_map(t_block *map);

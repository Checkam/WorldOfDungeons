/**
 *   \file generation.h
 *   \brief Module de generation de la map
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#include <block.h>



#define FREQ 0.01   /* third parameter of perlin2d function */
#define DEPTH 5     /* fourth parameter of perlin2d function */


#define HAUTEUR_SURFACE 4
#define PROFONDEUR_GROTTE 15
#define BEDROCK 3
#define SIZE_GROTTE 3
#define HAUTEUR_EAU MAX / 2.5

int gen_col(t_block **tab, int x) ;
void init_map(t_block *map);

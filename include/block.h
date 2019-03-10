/**
 *   \file block.h
 *   \brief Module block fonction et structure
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <couleurs.h>

#define NB_BLOCK 10

/**
 \enum t_materiaux
 \brief Enum de tous les materiaux qui existe
**/
typedef enum { AIR, HERBE, TERRE, EAU, SABLE, FEUILLE, BOIS, ROCHE, NEIGE, GLACE, DIAMAND } t_materiaux;

/**
 \struct t_block_type
 \brief Structure d'une type de block
**/
typedef struct block_type_s {
  t_materiaux materiau;
  char *nom;
  int resistance;

  char *texture_sdl;
  char *texture_term;
} t_block_type;


/**
 \enum t_block
 \brief Structure d'un block
**/
typedef struct block_s {
  int id, x, y;
} t_block;

#endif

char *BLOCK_GetTexture_sdl(int id);
char *BLOCK_GetTexture_term(int id);

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
#include <SDL2/SDL.h>
#include <erreur.h>

#define NB_BLOCK 23

/**
 \enum t_materiaux
 \brief Enum de tous les materiaux qui existe
**/
typedef enum {
  AIR=0,
  HERBE=1,
  TERRE=2,
  EAU=3,
  SABLE=4,
  FEUILLE=5,
  BOIS=6,
  ROCHE=7,
  NEIGE=8,
  GLACE=9,
  DIAMAND=10,
  GRAVIER=11,
  BRIQUE=12,
  PORTAIL_HAUT=13,
  PORTAIL_BAS=14,
  PLANT=15,
  MINERAI_CHARBON=16,
  MINERAI_CUIVRE=17,
  MINERAI_FER=18,
  MINERAI_ARGENT=20,
  MINERAI_OR=21,
  MINERAI_DIAMAND=22,
} t_materiaux;


/**
 \enum t_plan
 \brief Enum des plans de jeux
**/
typedef enum {
  PREMIER_PLAN,
  ARRIERE_PLAN
} t_plan;


/**
 \struct t_block_type
 \brief Structure d'une type de block
**/
typedef struct block_type_s {
  const t_materiaux materiau;
  const char *nom;
  const int resistance;
  const int cassable;

  char *texture_path_sdl;
  char *texture_term;

  SDL_Texture *texture_sdl;
} t_block_type;

/**
 \struct t_minerai
 \brief Structure d'un minerai
**/
typedef struct {

  t_block_type type;
  double valeur_min,valeur_max;
  int hauteur_min,hauteur_max;

} t_minerai;


/**
 \struct t_block
 \brief Structure d'un block
**/
typedef struct block_s {
  int x, y;
  uint8_t id,plan;
} t_block;

#endif

SDL_Texture *BLOCK_GetTexture_sdl(int id);
char *BLOCK_GetTexture_term(int id);

int BLOCK_estCassable(int id);

t_erreur BLOCK_DestroyTexture_sdl(SDL_Renderer *renderer);
t_erreur BLOCK_CreateTexture_sdl(SDL_Renderer *renderer);

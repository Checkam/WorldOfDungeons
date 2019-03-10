#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <couleurs.h>

#define NB_BLOCK 10

typedef enum { AIR, HERBE, TERRE, EAU, SABLE, FEUILLE, BOIS, ROCHE, NEIGE, GLACE, DIAMAND } materiaux_t;

typedef struct block_type_s {
  materiaux_t materiau;
  char *nom;
  int resistance;

  char *texture_sdl;
  char *texture_term;
} block_type_t;

typedef struct block_s {
  int id, x, y;
} block_t;

#endif

char *BLOCK_GetTexture_sdl(int id);
char *BLOCK_GetTexture_term(int id);

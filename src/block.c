/**
 *   \file block.c
 *   \brief Fonction sur les blocks
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#include <SDL2/SDL.h>
#include <block.h>
#include <erreur.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>

/**
  \var blocks
  \brief tableau de tous les blocks
**/
t_block_type blocks[NB_BLOCK] = {{AIR, "air", 0, NULL, NOIR, NULL},
                                 {HERBE, "herbe", 5, "./IMG/texture/herbe.png", VERT, NULL},
                                 {TERRE, "terre", 10, "./IMG/texture/terre.png", MARRON, NULL},
                                 {EAU, "eau", 0, "./IMG/texture/eau.png", BLEU, NULL},
                                 {SABLE, "sable", 5, "./IMG/texture/sable.png", JAUNE, NULL},
                                 {FEUILLE, "feuille", 3, "./IMG/texture/feuille.png", VERT, NULL},
                                 {BOIS, "bois", 15, "./IMG/texture/tronc.png", MARRON, NULL},
                                 {ROCHE, "roche", 50, "./IMG/texture/pierre.png", GRIS, NULL},
                                 {NEIGE, "neige", 3, "./IMG/texture/neige.png", BLANC, NULL},
                                 {GLACE, "glace", 10, "./IMG/texture/glace.png", CYAN, NULL},
                                 {GRAVIER, "gravier", 20, "./IMG/texture/gravier.png", GRIS, NULL}};

/**
 \fn char *BLOCK_GetTexture_term(int id)
 \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 \param id C'est le chiffre qui represente la texture rechercher
 \return la texture (une char * pour le terminal)
 **/
char *BLOCK_GetTexture_term(int id) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id)
      return blocks[i].texture_term;
  return NOIR;
}

/**
 * \fn SDL_Texture *BLOCK_GetTexture_sdl(int id)
 * \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 * \param id C'est le chiffre qui represente la texture rechercher
 * \return Renvoie la texture SDL2
 **/
SDL_Texture *BLOCK_GetTexture_sdl(int id) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id) {
      return blocks[i].texture_sdl;
    }
  return NULL;
}

void BLOCK_afficher_type(t_block_type b) {
  printf("materiau : %d nom : %s resistance : %d, path texture sdl : %s texture dans le terminal : %s\n", b.materiau, b.nom, b.resistance,
         b.texture_path_sdl, b.texture_term);
}

void BLOCK_afficher_coord(t_block b) { printf("id : %d , x : %d , y : %d\n", b.id, b.x, b.y); }

t_erreur BLOCK_CreateTexture_sdl(SDL_Renderer *renderer) {
  for (int i = 0; i < NB_BLOCK; i++) {
    if (blocks[i].texture_path_sdl != NULL) {
      SDL_Texture *texture_block;
      Create_IMG_Texture(renderer, blocks[i].texture_path_sdl, &texture_block);
      blocks[i].texture_sdl = texture_block;
    } else {
      blocks[i].texture_sdl = NULL;
    }
  }
  return OK;
}

t_erreur BLOCK_DestroyTexture_sdl(SDL_Renderer *renderer) {
  for (int i = 0; i < NB_BLOCK; i++) {
    if (blocks[i].texture_sdl != NULL) {
      SDL_DestroyTexture(blocks[i].texture_sdl);
    }
    blocks[i].texture_sdl = NULL;
  }
  return OK;
}

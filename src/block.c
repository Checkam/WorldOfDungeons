
#include <block.h>
#include <stdio.h>
#include <stdlib.h>

static block_type_t blocks[NB_BLOCK] = {{AIR, "air", 0, NULL, NOIR},
                                        {HERBE, "herbe", 5, "./IMG/texture/herbe.bmp", VERT},
                                        {TERRE, "terre", 10, "./IMG/texture/terre.bmp", MARRON},
                                        {EAU, "eau", 0, "./IMG/texture/eau.bmp", BLEU},
                                        {SABLE, "sable", 5, "./IMG/texture/terre.bmp", JAUNE},
                                        {FEUILLE, "feuille", 3, "./IMG/texture/feuille.bmp", VERT},
                                        {BOIS, "bois", 15, "./IMG/texture/tronc.bmp", MARRON},
                                        {ROCHE, "roche", 50, "./IMG/texture/pierre.bmp", GRIS},
                                        {NEIGE, "neige", 3, "./IMG/texture/neige.bmp", BLANC},
                                        {GLACE, "glace", 10, "./IMG/texture/neige.bmp", CYAN}};

/**
 \fn char *CouleurBlock(int id, block_type2_t blocks[])
 \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 \param id C'est le chiffre qui represente la texture rechercher
 \param blocks un tableau de block
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
 * \fn SDL_Texture *BLOCK_texture_sdl(SDL_Renderer *renderer, int id)
 * \brief Chercher la texture d'un block par rapport a son id et renvoie la texture terminal de ce block
 * \param id C'est le chiffre qui represente la texture rechercher
 * \param blocks un tableau de block
 * \return la texture (une char * pour le terminal)
 **/
char *BLOCK_GetTexture_sdl(int id) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id) {
      return blocks[i].texture_sdl;
    }
  return NULL;
}

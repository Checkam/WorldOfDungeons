/**
 *   \file block.c
 *   \brief Fonction sur les blocks
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#include <SDL2/SDL.h>
#include <block.h>
#include <commun.h>
#include <erreur.h>
#include <outils_SDL.h>
#include <stdio.h>
#include <stdlib.h>

/**
  \var blocks
  \brief tableau de tous les blocks
**/
static t_block_type blocks[NB_BLOCK] = {{AIR, "air", 0, 0, NULL, NOIR, NULL},
                                        {HERBE, "herbe", 10, 1, "./IMG/texture/block/herbe.png", VERT, NULL},
                                        {TERRE, "terre", 10, 1, "./IMG/texture/block/terre.png", MARRON, NULL},
                                        {EAU, "eau", 0, 0, "./IMG/texture/block/eau.png", BLEU, NULL},
                                        {SABLE, "sable", 5, 1, "./IMG/texture/block/sable.png", JAUNE, NULL},
                                        {FEUILLE, "feuille", 3, 1, "./IMG/texture/block/feuille.png", VERT, NULL},
                                        {BOIS, "bois", 15, 1, "./IMG/texture/block/tronc.png", MARRON, NULL},
                                        {ROCHE, "roche", 20, 1, "./IMG/texture/block/pierre.png", GRIS, NULL},
                                        {NEIGE, "neige", 3, 1, "./IMG/texture/block/neige.png", BLANC, NULL},
                                        {GLACE, "glace", 10, 1, "./IMG/texture/block/glace.png", CYAN, NULL},
                                        {GRAVIER, "gravier", 10, 1, "./IMG/texture/block/gravier.png", GRIS, NULL},
                                        {BRIQUE, "brique", 40, 1, "./IMG/texture/block/brique.png", MARRON, NULL},
                                        {PORTAIL_HAUT, "portail_haut", 100, 0, "./IMG/texture/block/portail_donjon_haut.png", NOIR, NULL},
                                        {PORTAIL_BAS, "portail_bas", 100, 0, "./IMG/texture/block/portail_donjon_bas.png", NOIR, NULL},
                                        {MINERAI_CHARBON, "minerai_charbon", 20, 0, "./IMG/texture/block/minerai_charbon.png", NOIR, NULL},
                                        {MINERAI_CUIVRE, "minerai_cuivre", 25, 0, "./IMG/texture/block/minerai_cuivre.png", JAUNE, NULL},
                                        {MINERAI_FER, "minerai_fer", 50, 0, "./IMG/texture/block/minerai_fer.png", GRIS, NULL},
                                        {MINERAI_ARGENT, "minerai_argent", 55, 0, "./IMG/texture/block/minerai_argent.png", GRIS, NULL},
                                        {MINERAI_OR, "minerai_or", 70, 0, "./IMG/texture/block/minerai_or.png", JAUNE, NULL},
                                        {MINERAI_DIAMAND, "minerai_diamand", 150, 0, "./IMG/texture/block/minerai_diamand.png", CYAN, NULL},
                                        {PLANT, "plant", 5, 0, "./IMG/texture/block/herbe_plant.png", VERT, NULL},
                                        {BEDROCK, "bedrock", 1000, 0, "./IMG/texture/block/bedrock.png", NOIR, NULL}};

/**
 * \var minerais
 * \brief tableau de tous les minerais
**/
t_minerai minerais[NB_MINERAI] = {
    {MINERAI_CHARBON, 0.73555, 0.73555 + 0.005, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 1.25), MAX},
    {MINERAI_CUIVRE, 0.43555, 0.43555 + 0.005, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 1.25), MAX},
    {MINERAI_FER, 0.63333, 0.63333 + 0.004, 0, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 10)},
    {MINERAI_ARGENT, 0.47333, 0.47333 + 0.003, 0, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 4)},
    {MINERAI_OR, 0.39111, 0.39111 + 0.003, 0, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 2)},
    {MINERAI_DIAMAND, 0.55555, 0.55555 + 0.002, 0, HAUTEUR_MINIMUN - (HAUTEUR_MINIMUN / 1.25)},
};

t_minerai *BLOCK_GetMinerai() { return minerais; }

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

/**
 * \fn int BLOCK_estCassable(int id)
 * \brief Permet de savoir si un block est cassable ou non
 * \param id l'id est le materiau block rechercher
 * \return Renvoie 1 si cassable 0 si incassable
 **/
int BLOCK_estCassable(int id) {
  int i;
  for (i = 0; i < NB_BLOCK; i++)
    if (blocks[i].materiau == id) {
      return blocks[i].cassable;
    }
  return 0;
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

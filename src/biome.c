#include <biome.h>
#include <block.h>
#include <commun.h>
#include <liste.h>
#include <perlin.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \fn void changeBiome(int x, int y)
 * \brief Fonction pour changer de biome si les condi
 * \param x coordonné abscisse
 * \param y coordonné ordonnée
 * \return Ne retourne rien
**/

static t_liste biomes;

void changeBiome(int x, int y) {
  if (x % W_BIOME == SEED % W_BIOME) {
    // Génere un chiffre entre 0 et le nombre de biome qui existe
    biome = (int)((double)x * perlin2d(x - 1, y, FREQ, DEPTH) * SEED + 1) % NB_BIOME;
  }
}

void BIOME_init() {
  init_liste(&biomes);
  t_biome *b = BIOME_CreateBiome(FORET);
  b = BIOME_CreateBiome(TAIGA);
  b = BIOME_CreateBiome(TOUNDRA);
  BIOME_AddLayer(b, NEIGE, 10, 100);
}

t_biome *BIOME_rechercheParType(t_biome_type type) {
  t_biome *b = malloc(sizeof(t_biome));
  for (en_tete(&biomes); !hors_liste(&biomes); suivant(&biomes)) {
    valeur_elt(&biomes, (void **)&b);
    if (b->type == type)
      return b;
  }
  free(b);
  return NULL;
}

t_biome *BIOME_CreateBiome(t_biome_type type) {
  t_biome *b = malloc(sizeof(t_biome));
  b->type = type;
  b->layers = malloc(sizeof(t_liste));
  init_liste(b->layers);
  b->nb_layers = 0;
  ajout_droit(&biomes, b);
  return b;
}

void BIOME_AddLayer(t_biome *b, t_materiaux block_type, int min, int max) {
  t_layer *layer = malloc(sizeof(t_layer));
  layer->hauteur_max = max;
  layer->hauteur_min = min;
  layer->block_type = block_type;
  ajout_droit(b->layers, layer);
  modif_elt(&biomes, b);
}

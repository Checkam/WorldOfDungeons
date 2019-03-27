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

t_liste biomes;

t_biome_type BIOME_change_type(int x, int y) { return (t_biome_type)(x / W_BIOME) % NB_BIOME; }

void BIOME_init() {
  init_liste(&biomes);
#include <init_biome.h>
}

t_biome *BIOME_rechercheParType(t_biome_type type) {
  t_biome *b;
  for (en_tete(&biomes); !hors_liste(&biomes); suivant(&biomes)) {
    valeur_elt(&biomes, (void **)&b);
    if (b->type == type)
      return b;
  }
  return NULL;
}

void BIOME_afficher_type() {}

t_biome *BIOME_CreateBiome(t_biome_type type) {
  t_biome *b = malloc(sizeof(t_biome));
  b->type = type;
  b->layers = malloc(sizeof(t_layer) * MAX);
  b->nb_layers = 0;
  ajout_droit(&biomes, b);
  return b;
}

void BIOME_AddLayer(t_biome *b, t_materiaux block_type, int nb_couche) {
  b->layers[b->nb_layers].nb_couche = nb_couche;
  b->layers[b->nb_layers].block_type = block_type;
  b->nb_layers++;
  modif_elt(&biomes, b);
}

void BIOME_Quit() {
  t_biome *b;
  for (en_queue(&biomes); !hors_liste(&biomes) || !liste_vide(&biomes); en_queue(&biomes)) {
    valeur_elt(&biomes, (void **)&b);
    BIOME_Destoy(b);
    oter_elt(&biomes, free);
  }
  detruire_liste(&biomes, free);
}

void BIOME_DestroyLayer(t_layer *layer) {
  if (layer != NULL) {
    free(layer);
  }
}
void BIOME_Destoy(t_biome *b) {
  if (b != NULL) {
    if (b->layers != NULL) {
      free(b->layers);
    }
  }
}

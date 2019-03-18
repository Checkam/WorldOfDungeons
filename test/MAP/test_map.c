#include <affichage.h>
#include <biome.h>
#include <erreur.h>
#include <generation.h>
#include <liste.h>
#include <map.h>
#include <stdio.h>
#include <stdlib.h>
#include <touches.h>

int main(int argc, char const *argv[]) {
  t_map *map = NULL;
  int boucle = 0;

  BIOME_init();

  printf("Création de la map et du repertoire : --");
  erreur_afficher(MAP_creer(&map, "World", 121212), "créer");
  printf("\n");

  printf("Nom map : %s avec comme SEED : %d\n", map->nom, map->SEED);

  while (boucle++ <= 50) {
    gen_col(map->list, boucle, DROITE);
  }

  AFF_map_term(map->list, 30, 80);

  printf("Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  printf("\n");

  printf("Chargement d'une map : -- ");
  erreur_afficher(MAP_charger(&map, "World"), "Chargement");
  printf("\n");

  printf("Nom map : %s avec comme SEED : %d\n", map->nom, map->SEED);

  printf("Suppression d'une map : -- ");
  erreur_afficher(MAP_supprimer(map), "Suppression");
  printf("\n");

  printf("Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  printf("\n");

  BIOME_Quit();
  return 0;
}

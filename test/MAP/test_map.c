#include <affichage.h>
#include <biome.h>
#include <chemin.h>
#include <erreur.h>
#include <generation.h>
#include <map.h>
#include <stdio.h>
#include <stdlib.h>
#include <touches.h>

int main(int argc, char const *argv[], char **env) {
  t_map *map = NULL;
  int boucle = 0;

  pwd_init(argv[0], getenv("PWD"));
  BIOME_init();

  fprintf(stderr, "Création de la map et du repertoire : --");
  erreur_afficher(MAP_creer(&map, "World1", 121212), "créer");
  fprintf(stderr, "\n");

  fprintf(stderr, "Sauvegarde des data de la map : --");
  //erreur_afficher(MAP_sauvegarder(map), "sauvegarder");
  fprintf(stderr, "\n");

  fprintf(stderr, "Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  fprintf(stderr, "\n");

  fprintf(stderr, "Création de la map et du repertoire : --");
  erreur_afficher(MAP_creer(&map, "World2", 121212), "créer");
  fprintf(stderr, "\n");

  fprintf(stderr, "Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  fprintf(stderr, "\n");

  fprintf(stderr, "Création de la map et du repertoire : --");
  erreur_afficher(MAP_creer(&map, "World3", 121212), "créer");
  fprintf(stderr, "\n");

  fprintf(stderr, "Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  fprintf(stderr, "\n");

  fprintf(stderr, "Création de la map et du repertoire : --");
  erreur_afficher(MAP_creer(&map, "World4", 121212), "créer");
  fprintf(stderr, "\n");

  fprintf(stderr, "Nom map : %s avec comme SEED : %d\n", map->nom, map->SEED);

  while (boucle++ <= 50) {
    gen_col(map->list, boucle, DROITE);
  }

  AFF_map_term(map->list, 30, 80);

  fprintf(stderr, "Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  fprintf(stderr, "\n");

  fprintf(stderr, "Chargement d'une map : -- ");
  erreur_afficher(MAP_charger(&map, "World4"), "Chargement");
  fprintf(stderr, "\n");

  fprintf(stderr, "Nom map : %s avec comme SEED : %d\n", map->nom, map->SEED);

  fprintf(stderr, "Suppression d'une map : -- ");
  erreur_afficher(MAP_supprimer(map), "Suppression");
  fprintf(stderr, "\n");

  fprintf(stderr, "Destruction de la zone mémoire pointer par map : -- ");
  erreur_afficher(MAP_detruction(&map), "Destruction");
  fprintf(stderr, "\n");

  BIOME_Quit();
  pwd_quit();
  return 0;
}

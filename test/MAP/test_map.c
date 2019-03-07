#include <stdio.h>
#include <stdlib.h>
#include <map.h>

int main(int argc, char const *argv[]) {
  t_map * map = NULL;
  printf("Création de la map et du repertoire : -- %s\n",MAP_creer(&map,"World 1",121212) == OK? "OK" : "NOK");

  printf("Nom map : %s avec comme SEED : %d\n",map->nom,map->SEED);

  printf("Suppression d'une map : -- %s\n",MAP_supprimer(map) == OK? "OK" : "NOK");

  printf("Destruction de la zone mémoire pointer par map : -- %s\n",MAP_detruction(&map) == OK? "OK" : "NOK");

  printf("Chargement d'une map : -- %s\n",MAP_charger(&map,"Coucou") == OK? "OK" : "NOK");

  printf("Nom map : %s avec comme SEED : %d\n",map->nom,map->SEED);

  printf("Destruction de la zone mémoire pointer par map : -- %s\n",MAP_detruction(&map) == OK? "OK" : "NOK");

  return 0;
}

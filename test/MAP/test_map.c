#include <stdio.h>
#include <stdlib.h>
#include <map.h>

int main(int argc, char const *argv[]) {
  t_map * map = MAP_creer("Coucou",121212);
  printf("Nom map : %s",map->nom);
  MAP_supprimer(&map);
  return 0;
}

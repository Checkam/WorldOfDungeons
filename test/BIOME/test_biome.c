#include <biome.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env) {
  BIOME_init();
  t_biome *b2 = BIOME_rechercheParType(TOUNDRA);
  printf("nb_couche : %d block: %d\n", b2->layers[1].nb_couche, b2->layers[1].block_type);

  BIOME_Quit();
  return OK;
}

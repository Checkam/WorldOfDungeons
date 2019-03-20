#include <perlin.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5000

int main(int argc, char **argv, char **env)
{
  float ETAL = 2;
  int NB_B = 5, NB = NB_B * ETAL;
  int check = 0;

  if (!(NB_B % 2)) check = 1;
  int tab[NB];
  int i;
  for (i = 0; i < NB; i++)
    tab[i] = 0;
  int x = 0, res;
  for (x = 0; x < N; x++){
    res = perlin2d(x,x,FREQ,DEPTH) * NB;
    if (res <= NB/2 - NB_B/2) res = NB/2 - NB_B/2;
    if (res >= NB/2 + NB_B/2 - check) res = NB/2 + NB_B/2 - check;
    //printf("%d ", res - NB_B/2 - 1 + check);
    tab[res]++;
  }
  
  printf("\n");
  for (i = 0; i < NB; i++)
    printf("%d ", tab[i] * 100 / N);
  printf("\n");

  return 0;
}

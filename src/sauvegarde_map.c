#include <commun.h>
#include <stdio.h>

void save_tab(FILE *fichier, int *tab) {
  int i;
  for (i = 0; i < MAX; i++) {
    switch (*(tab + i)) {
    case 0: /* Air */
      fprintf(fichier, " ");
      break;
    case 1: /* Herbe */
      fprintf(fichier, "V");
      break;
    case 2: /* Eau */
      fprintf(fichier, "~");
      break;
    case 3: /* Sable */
      fprintf(fichier, "S");
      break;
    case 4: /* Feuille */
      fprintf(fichier, "A");
      break;
    case 5: /* Tronc */
      fprintf(fichier, "T");
      break;
    default: /* Roche */
      fprintf(fichier, "#");
      break;
    }
  }
  fprintf(fichier, "\n");
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* j'ai dit que cette fonction de vait etre commentée !! */


/* A QUOI CA SERT ??? */

int seed_part(const char *const seed)
{
    char * chaine = malloc(sizeof(char) * (strlen(seed) + 1));
    
    int i;
    for(i = 0; seed[i]; i++)
        *(chaine + i) = *(seed + i);
    *(chaine + i) = 0;
    
    int res = atoi(chaine);
    free(chaine);
    return res;
}
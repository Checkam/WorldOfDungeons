#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv, char **env){

    long seed = 15115;
    
    int i, j;
    for(j = 0; j < 3; j++, seed--){
        printf("SEED=%d\n", seed);
        for(i = 0; i < 30; i++){
            srand(seed * i);
            int taille = rand()%10;
            while(taille--)
                printf("#");
            printf("\n");
        }
        printf("--------\n");
    }

     //srand(seed * 5);
     //printf("%f\n", rand()/(float)RAND_MAX);
    return EXIT_SUCCESS;
}
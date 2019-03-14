#include <stdio.h>
#include <stdlib.h>
//#include <chemin.h>
//#include <SDL2/SDL.h>

int main(int argc, char **argv, char **env){

    int SEED = 15144;
    int i;
    for(i = 1; i < 100; i++){
        srand(SEED * i);
        printf("%d\n", rand()%i);
    }

    return EXIT_SUCCESS;
}
#include <fps.h>

#include <stdio.h>

int main () {

    fps_init();

    int i;
    double comp;

    while ( 1 ) {

        for ( i = 0 ; i < 10000000 ; i++ );

        comp = fps();
        printf("multiplieur : %g\n", comp);
    }
}
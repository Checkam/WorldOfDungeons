#include <item.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module touche fonctionne. SDL doit etre initialiser a la video au minimum.*/

	init_item();
	
	exit_item();
	
	
	return 0;

}

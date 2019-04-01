#include <item.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module item fonctionne */

	t_liste_item *item = NULL;
	uint8_t i = 0;

	init_item();

	#ifdef DEBUG
		uint8_t err;
		if ( ( err = block_to_item( NEIGE, &item )) ) {
			printf("Erreur : code sortie %d de block_to_item()\n", err);
			return err;
		}
	#else
		block_to_item( NEIGE, &item);
	#endif

	i = 0;

	while ( ( item + i )->item != I_END ) {

		printf("	%d fois %d\n", ( item + i )->nbDrop, ( item + i )->item );
		i++;
	}

	exit_item( &item );
	
	return 0;

}
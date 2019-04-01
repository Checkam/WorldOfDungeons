#include <inventaire.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module inventaire fonctionne */

	t_inventaire *inventaire = create_inventaire();

	#ifdef DEBUG
		if ( alloc_item(inventaire, 5) ) {

			printf("erreur : impossible d'allouer la memoire necessaire\n");
			return 1;
		}
	#else
		alloc_item(&inventaire, 5);
	#endif

	printf("Taille du bloc memoire : %ld\n", sizeof(t_inventaire_item) );

	for ( uint16_t i = 0 ; i < inventaire->nbItem ; i++ )
		printf("%p\n", (inventaire->inventaire) + i );

	#ifdef DEBUG
		if ( alloc_item(&inventaire, 10) ) {

			printf("erreur : impossible d'allouer la memoire necessaire\n");
			return 1;
		}
	#else
		alloc_item(&inventaire, 10);
	#endif

	printf("\n");

	for ( uint16_t i = 0 ; i < inventaire->nbItem ; i++ )
		printf("%p\n", (inventaire->inventaire) + i );

	free_inventaire(inventaire);
}
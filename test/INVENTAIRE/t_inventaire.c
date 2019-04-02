#include <inventaire.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module inventaire fonctionne */

	#ifdef DEBUG
		printf("DEBUG enable\n");
	#endif

	/*	------------------------------------------------|
	|	Creation d'un inventaire						|
	|	-----------------------------------------------*/

	t_inventaire *inventaire = create_inventaire();

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 5 items		|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		if ( alloc_item(inventaire, 5) ) {

			fprintf(stderr, "erreur : impossible d'allouer la memoire necessaire ligne %d %s\n", __LINE__, __FILE__);
			return 1;
		}
	#else
		alloc_item(inventaire, 5);
	#endif

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/



	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 10 items		|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		if ( alloc_item(inventaire, 10) ) {

			printf("erreur : impossible d'allouer la memoire necessaire\n");
			return 1;
		}
	#else
		alloc_item(&inventaire, 10);
	#endif

	/*	------------------------------------------------|
	|	Note :											|
	|	Les items sont tjs present dans l'inventaire	|
	|	-----------------------------------------------*/


	/*	------------------------------------------------|
	|	Liberation de la zone memoire de l'inventaire	|
	|	-----------------------------------------------*/

	free_inventaire(inventaire);
}
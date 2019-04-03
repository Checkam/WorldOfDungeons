#include <inventaire.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int main ( int argc, char ** argv ) {
/* Ce main est le MINIMUM afin que le module inventaire fonctionne */

	#ifdef DEBUG
		fprintf(stderr, "DEBUG enable\n");
	#endif

	init_item();

	/*	------------------------------------------------|
	|	Creation d'un inventaire						|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		fprintf(stderr, "Creation d'inventaire");
	#endif

	t_inventaire *inventaire = create_inventaire();

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 5 items		|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		fprintf(stderr, " - OK\nAllocation memoire");
	#endif

	alloc_item(inventaire, 5);

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		fprintf(stderr, " - OK\nAjout d'item -> etape 1 : creation de la liste");
	#endif

	t_liste *liste = malloc(sizeof(t_liste));
	init_liste(liste);
	en_tete(liste);

	t_liste_item *item = malloc( sizeof(t_liste_item) );
	(item)->nbDrop = 55;
	(item)->item = I_ROCHE;

	ajout_droit(liste, (void *)item );

	#ifdef DEBUG
		fprintf(stderr, " - OK\nAjout d'item -> etape 2 : ajout dans l'inventaire");
	#endif

	ajout_item_dans_inventaire( inventaire, liste);

	#ifdef DEBUG
		if ( liste_vide(liste))
			fprintf(stderr, " - OK\n");
		else
			fprintf(stderr, "ERREUR -> liste non vide\n");
	#endif

	afficher_inventaire ( inventaire );

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 10 items		|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		fprintf(stderr, "Allocation d'une nouvelle zone memoire");
	#endif

	alloc_item(inventaire, 10);

	#ifdef DEBUG
		fprintf(stderr, " - OK\najout de nouveaux item");
	#endif

	en_tete(liste);

	t_liste_item *item2 = malloc( sizeof(t_liste_item) );
	(item2)->nbDrop = 15;
	(item2)->item = I_TERRE;

	ajout_droit(liste, (void *)item2 );

	t_liste_item *item3 = malloc( sizeof(t_liste_item) );
	(item3)->nbDrop = 25;
	(item3)->item = I_BOULE_NEIGE;

	ajout_droit(liste, (void *)item3 );

	ajout_item_dans_inventaire( inventaire, liste);

	afficher_inventaire ( inventaire );

	/*	------------------------------------------------|
	|	Note :											|
	|	Les items sont tjs present dans l'inventaire	|
	|	-----------------------------------------------*/

	/*	------------------------------------------------|
	|	Liberation de la zone memoire de l'inventaire	|
	|	-----------------------------------------------*/

	#ifdef DEBUG
		printf(" - OK\nLiberation de la zone memoire");
	#endif

	free_inventaire(inventaire);

	t_liste_item *aa = NULL;

	exit_item(&aa);
	detruire_liste(liste, free);

	#ifdef DEBUG
		printf(" - OK\n");
	#endif
}
#include <inventaire.h>

#include <stdio.h>

int main ( int argc, char ** argv, char **env ) {
/* Ce main est le MINIMUM afin que le module inventaire fonctionne */

	WIDTH = 800;
	HEIGHT = 450;

	scaleW = DEFAULT_SIZE_SCREEN_W / WIDTH;
	scaleH = DEFAULT_SIZE_SCREEN_H / HEIGHT;

	uiScale = 100;

	pwd_init( argv[0], getenv("PWD"));

	SDL_Init( SDL_INIT_VIDEO );

	SDL_Renderer *renderer;
	SDL_Window *window = SDL_CreateWindow("Inventaire test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	printf("initialisation item\n");

	init_item(renderer);
	inventaire_init( renderer);

	/*	------------------------------------------------|
	|	Creation d'un inventaire						|
	|	-----------------------------------------------*/

	printf("creation d'inventaire\n");

	t_inventaire *inventaire = create_inventaire();

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 5 items		|
	|	-----------------------------------------------*/

	alloc_item(inventaire, 5);

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/

	printf("ajout d'item\n");

	t_liste *liste = malloc(sizeof(t_liste));
	init_liste(liste);
	en_tete(liste);

	/*t_liste_item *item = malloc( sizeof(t_liste_item) );
	(item)->nbDrop = 15;
	(item)->item = I_ROCHE;

	ajout_droit(liste, (void *)item );

	ajout_item_dans_inventaire( inventaire, liste);*/

	afficher_inventaire ( inventaire );

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 10 items		|
	|	-----------------------------------------------*/

	alloc_item(inventaire, 10);

	/*	------------------------------------------------|
	|	Note :											|
	|	Les items sont tjs present dans l'inventaire	|
	|	-----------------------------------------------*/

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/

	/*en_tete(liste);

	t_liste_item *item2 = malloc( sizeof(t_liste_item) );
	(item2)->nbDrop = 15;
	(item2)->item = I_TERRE;

	ajout_droit(liste, (void *)item2 );*/

	t_liste_item *item3 = malloc( sizeof(t_liste_item) );
	(item3)->nbDrop = 25;
	(item3)->item = I_BOULE_NEIGE;

	ajout_droit(liste, (void *)item3 );

	ajout_item_dans_inventaire( inventaire, liste);

	afficher_inventaire ( inventaire );

	/*	------------------------------------------------|
	|	Affichage dans la SDL							|
	|	-----------------------------------------------*/

	/*SDL_RenderCopy(renderer, ( tabItem + I_BOULE_NEIGE )->texture, NULL, &rdst );*/

	/*for ( uint8_t i = 0 ; i < 10 ; i++ ) {*/

		/*SDL_RenderCopy(renderer, ( tabItem + I_BOULE_NEIGE )->texture, NULL, &rdst );*/
		/*SDL_RenderCopy(renderer, bordure, NULL, &rdst );*/

	SDL_afficher_barre_action( renderer, inventaire, 9);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	SDL_Delay(3000);

	/*SDL_FreeSurface(img);*/

	/*	------------------------------------------------|
	|	Liberation de la zone memoire de l'inventaire	|
	|	-----------------------------------------------*/

	SDL_DestroyWindow(window);

	SDL_Quit();

	pwd_quit();

	free_inventaire(inventaire);

	t_liste_item *aa = NULL;

	exit_item(&aa);
	detruire_liste(liste, free);

    free(liste);
}
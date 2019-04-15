#include <inventaire.h>

#include <touches.h>
#include <block.h>

#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main ( int argc, char ** argv, char **env ) {
/* Ce main est le MINIMUM afin que le module inventaire fonctionne */

	/*	------------------------------------------------|
	|	Def des constantes								|
	|	-----------------------------------------------*/

	WIDTH = /*1920*/1000;
	HEIGHT = /*1080*/600;

	scaleW = DEFAULT_SIZE_SCREEN_W / WIDTH;
	scaleH = DEFAULT_SIZE_SCREEN_H / HEIGHT;

	uiScale = 100;

	/*	------------------------------------------------|
	|	Initialisation des modules						|
	|	-----------------------------------------------*/

	uint8_t *ks;
	configTouches_t *ct;

	pwd_init( argv[0], getenv("PWD"));
	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	SDL_init_touches(&ks, &ct);

	SDL_Renderer *renderer;
	SDL_Window *window = SDL_CreateWindow("Inventaire test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, /*SDL_WINDOW_FULLSCREEN*/ SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	init_item(renderer);
	inventaire_init( renderer);

	/*	------------------------------------------------|
	|	Creation d'un inventaire						|
	|	-----------------------------------------------*/

	t_inventaire *inventaire = create_inventaire();

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 5 items		|
	|	-----------------------------------------------*/

	alloc_item(inventaire, 5);

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/

	t_liste *liste = malloc(sizeof(t_liste));
	init_liste(liste);
	en_tete(liste);

	/*t_liste_item *item = malloc( sizeof(t_liste_item) );
	(item)->nbDrop = 70;
	(item)->item = I_TERRE;

	ajout_droit(liste, (void *)item );

	ajout_item_dans_inventaire( inventaire, liste);

	afficher_inventaire ( inventaire );*/

	/*	------------------------------------------------|
	|	Allocation d'une zone memoire de 10 items		|
	|	-----------------------------------------------*/

	alloc_item(inventaire, 3);

	/*	------------------------------------------------|
	|	Note :											|
	|	Les items sont tjs present dans l'inventaire	|
	|	-----------------------------------------------*/

	/*	------------------------------------------------|
	|	Ajout d'item dans l'inventaire					|
	|	-----------------------------------------------*/

	/*en_tete(liste);*/

	/*t_liste_item *item2 = malloc( sizeof(t_liste_item) );
	(item2)->nbDrop = 15;
	(item2)->item = I_TERRE;

	ajout_droit(liste, (void *)item2 );

	t_liste_item *item3 = malloc( sizeof(t_liste_item) );
	(item3)->nbDrop = 25;
	(item3)->item = I_BOULE_NEIGE;

	t_liste_item *item4 = malloc( sizeof(t_liste_item) );
	(item4)->nbDrop = 25;
	(item4)->item = I_SABLE;

	t_liste_item *item5 = malloc( sizeof(t_liste_item) );
	(item5)->nbDrop = 25;
	(item5)->item = I_PIERRE;

	t_liste_item *item6 = malloc( sizeof(t_liste_item) );
	(item6)->nbDrop = 126;
	(item6)->item = I_BOULE_NEIGE;

	ajout_droit(liste, (void *)item3 );
	ajout_droit(liste, (void *)item4 );
	ajout_droit(liste, (void *)item5 );
	ajout_droit(liste, (void *)item6 );*/

	/*	------------------------------------------------|
	|	Affichage dans la SDL							|
	|	-----------------------------------------------*/

	inventaire_changer_constante(5);

	/*while ( !SDL_touche_appuyer(ks, ESCAPE)) {*/

		casser_block( TERRE, &liste );
		casser_block( NEIGE, &liste );
		ajout_item_dans_inventaire( inventaire, liste);

		SDL_reset_wheel_state(ks);
		SDL_touches( ks, ct);
		/*SDL_afficher_barre_action( renderer, inventaire, SDL_wheel_state(ks));*/
		inventaire_afficher(renderer, inventaire);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(100);

		t_enr_inventaire enrInv;

		enrInv.x = 10;
		enrInv.y = 20;
		enrInv.inventaire = inventaire;

		inventaire_enregistrer("", &enrInv);

		afficher_inventaire( inventaire);

		free_inventaire( inventaire);

		inventaire_recuperer( "", &inventaire, 10, 20);

		afficher_inventaire( inventaire);
	/*}*/

	/*	------------------------------------------------|
	|	Liberation de la zone memoire de l'inventaire	|
	|	-----------------------------------------------*/

	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	pwd_quit();

	free_inventaire(inventaire);

	exit_item(NULL);
	detruire_liste(liste, free);

    free(liste);
}
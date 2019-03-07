#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <ctype.h>

#include <touches.h>

#include <SDL2/SDL.h>

int TERM_touches () {

	int t[100];

	int j, max;
	int c;

	initscr();
		
	timeout(1);
	c = getch();
	j = 0;

	while ( c != -1 ) {
		
		t[j] = c;
		c = getch();
		j++;
	}

	printf("system clear ...");
	system("clear");

	max = j;
	j = 0;

	mvprintw(0, 0, "affichage : ");

	while ( j < max ) {

		printw("%c", t[j]);
		j++;
	}

	endwin();

	return 0;
}

int SDL_touches( Uint8 *keybaordState, configTouches_t *configuration ) {

	SDL_Event event;

	Uint16 i = 0;

	while ( SDL_PollEvent(&event) ) {

		if ( event.type = SDL_QUIT )
			(keyboardState + QUITTER ) = PRESSED;
		else {

			if ( event.key.type == SDL_KEYUP ) {
				
				while ( event.key.keysym.sym != (configuration + i)->keycode )
					i++;

				(keyboardState + i) = RELEASED;
			}
		}
	}
}

int SDL_init_touches( Uint8 *keyboardState, configTouches_t *configuration ) {

	Uint16 i;

	keyboardState = malloc( sizeof( Uint16 ) * NB_TOUCHES );

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		* ( keybordState + i ) = RELEASED;
	}

	/* pour l'instant a l'arrache, ce sera prope avec les fichiers json de tib*/
	(( configuration + QUITTER )->descriptif) = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	*(( configuration + QUITTER )->descriptif) = "quiter";
	( configuration + QUITTER )->keyCode = NULL_TOUCHE;

	(( configuration + AVANCER )->descriptif) = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	*(( configuration + AVANCER )->descriptif) = "avancer";
	( configuration + AVANCER )->keyCode = SDLK_z;

	(( configuration + RECULER )->descriptif) = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	*(( configuration + RECULER )->descriptif) = "reculer";
	( configuration + RECULER )->keyCode = SDLK_s;

	(( configuration + GAUCHE )->descriptif) = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	*(( configuration + GAUCHE )->descriptif) = "gauche";
	( configuration + GAUCHE )->keyCode = SDLK_q;

	(( configuration + DROITE )->descriptif) = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	*(( configuration + DROITE )->descriptif) = "droite";
	( configuration + DROITE )->keyCode = SDLK_d;
}


int SDL_exit_touches ( Uint8 *keyboardState, configTouches_t *configuration ) {
/* fermeture propre du module touches pour SDL */

	Uint16 i;

	free( keyboardState );

	for ( i = 0 ; i < NB_TOUCHES ; i++ )
		free( (configuration + i)->descriptif);

	return 0;
}

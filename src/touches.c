/*#include <ncurses.h>*/
#include <stdlib.h>

#include "touches.h"

#include <SDL2/SDL.h>

/*int TERM_touches () {

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
}*/

int SDL_init_touches( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* permet d'allouer les zone memoire necessaire au bon fonctionnement du module touches */

	short i;

	*keyboardState = malloc( sizeof( short ) * NB_TOUCHES );
	*configuration = malloc( sizeof( configTouches_t) * NB_TOUCHES);

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		* ( (*keyboardState) + i ) = RELEASED;
		((*configuration) + i)->descriptif = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	}

	/* pour l'instant a l'arrache, ce sera prope avec les fichiers json de tib*/
	(( (*configuration) + QUITTER )->descriptif) = "quiter";
	( (*configuration) + QUITTER )->keyCode = NULL_TOUCHE;

	(( (*configuration) + AVANCER )->descriptif) = "avancer";
	( (*configuration) + AVANCER )->keyCode = SDLK_z;

	(( (*configuration) + RECULER )->descriptif) = "reculer";
	( (*configuration) + RECULER )->keyCode = SDLK_s;

	(( (*configuration) + GAUCHE )->descriptif) = "gauche";
	( (*configuration) + GAUCHE )->keyCode = SDLK_q;

	(( (*configuration) + DROITE )->descriptif) = "droite";
	( (*configuration) + DROITE )->keyCode = SDLK_d;

	return 0;
}

int SDL_touches( uint8_t *keyboardState, configTouches_t *configuration ) {
	/* fonction a apeller a chaque image afin de recuperer l'etat ( appuyer ou relacher ) a chaque image */

	SDL_Event event;

	short i = 0;

	while ( SDL_PollEvent(&event) ) {

		switch( event.type ) {

			case SDL_QUIT:

				* ( keyboardState + QUITTER ) = PRESSED;
				break;

			case SDL_KEYDOWN:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES )
					i++;

				*( keyboardState + i ) = PRESSED;
				break;

			case SDL_KEYUP:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES )
					i++;

				*( keyboardState + i ) = RELEASED;
				break;
		}
	}

	return 0;
}

uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche ) {
	/* renvoie PRESSED si la touche ( short touche ) est appuyé, RELEASED sinon */

	if ( *( keyboardState + touche ) == PRESSED )
		return PRESSED;
	return RELEASED;
}

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration ) {
/* fermeture propre du module touches pour SDL */

	free( *keyboardState );

	/*for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		if ( ((*configuration) + i)->descriptif != NULL ) {

			printf("%s", ((*configuration) + i)->descriptif );
			free( ((*configuration) + i)->descriptif);
		}
	}*/

	free(*configuration);

	return 0;
}/*#include <ncurses.h>*/
#include <stdlib.h>

#include "touches.h"

#include <SDL2/SDL.h>

/*int TERM_touches () {

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
}*/

int SDL_init_touches( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* permet d'allouer les zone memoire necessaire au bon fonctionnement du module touches */

	short i;

	*keyboardState = malloc( sizeof( short ) * NB_TOUCHES );
	*configuration = malloc( sizeof( configTouches_t) * NB_TOUCHES);

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		* ( (*keyboardState) + i ) = RELEASED;
		((*configuration) + i)->descriptif = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF );
	}

	/* pour l'instant a l'arrache, ce sera prope avec les fichiers json de tib*/
	(( (*configuration) + QUITTER )->descriptif) = "quiter";
	( (*configuration) + QUITTER )->keyCode = NULL_TOUCHE;

	(( (*configuration) + AVANCER )->descriptif) = "avancer";
	( (*configuration) + AVANCER )->keyCode = SDLK_z;

	(( (*configuration) + RECULER )->descriptif) = "reculer";
	( (*configuration) + RECULER )->keyCode = SDLK_s;

	(( (*configuration) + GAUCHE )->descriptif) = "gauche";
	( (*configuration) + GAUCHE )->keyCode = SDLK_q;

	(( (*configuration) + DROITE )->descriptif) = "droite";
	( (*configuration) + DROITE )->keyCode = SDLK_d;

	return 0;
}

int SDL_touches( uint8_t *keyboardState, configTouches_t *configuration ) {
	/* fonction a apeller a chaque image afin de recuperer l'etat ( appuyer ou relacher ) a chaque image */

	SDL_Event event;

	short i = 0;

	while ( SDL_PollEvent(&event) ) {

		switch( event.type ) {

			case SDL_QUIT:

				* ( keyboardState + QUITTER ) = PRESSED;
				break;

			case SDL_KEYDOWN:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES )
					i++;

				*( keyboardState + i ) = PRESSED;
				break;

			case SDL_KEYUP:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES )
					i++;

				*( keyboardState + i ) = RELEASED;
				break;
		}
	}

	return 0;
}

uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche ) {
	/* renvoie PRESSED si la touche ( short touche ) est appuyé, RELEASED sinon */

	if ( *( keyboardState + touche ) == PRESSED )
		return PRESSED;
	return RELEASED;
}

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration ) {
/* fermeture propre du module touches pour SDL */

	free( *keyboardState );

	/*for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		if ( ((*configuration) + i)->descriptif != NULL ) {

			printf("%s", ((*configuration) + i)->descriptif );
			free( ((*configuration) + i)->descriptif);
		}
	}*/

	free(*configuration);

	return 0;
}

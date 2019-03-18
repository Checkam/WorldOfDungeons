#include <stdlib.h>

#include "touches.h"

#include <SDL2/SDL.h>

int SDL_init_touches( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* permet d'allouer les zone memoire necessaire au bon fonctionnement du module touches */

	short i;

	*keyboardState = malloc( sizeof( short ) * NB_TOUCHES );
	*configuration = malloc( sizeof( configTouches_t) * NB_TOUCHES);

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		* ( (*keyboardState) + i ) = RELEASED;
	}

	/* pour l'instant a l'arrache, ce sera prope avec les fichiers json de tib*/
	(( (*configuration) + QUITTER )->descriptif) = "quitter";
	( (*configuration) + QUITTER )->keyCode = NULL_TOUCHE;

	(( (*configuration) + AVANCER )->descriptif) = "avancer";
	( (*configuration) + AVANCER )->keyCode = SDLK_z;

	(( (*configuration) + RECULER )->descriptif) = "reculer";
	( (*configuration) + RECULER )->keyCode = SDLK_s;

	(( (*configuration) + GAUCHE )->descriptif) = "gauche";
	( (*configuration) + GAUCHE )->keyCode = SDLK_q;

	(( (*configuration) + DROITE )->descriptif) = "droite";
	( (*configuration) + DROITE )->keyCode = SDLK_d;

	(( (*configuration) + SPACE )->descriptif) = "sauter";
	( (*configuration) + SPACE )->keyCode = SDLK_SPACE;

	(( (*configuration) + SHIFT )->descriptif) = "shift";
	( (*configuration) + SHIFT )->keyCode = SDLK_LSHIFT;

	(( (*configuration) + ESCAPE )->descriptif) = "escape";
	( (*configuration) + ESCAPE )->keyCode = SDLK_ESCAPE;

	(( (*configuration) + SOURIS_BTN_1 )->descriptif) = "souris_gauche";
	( (*configuration) + SOURIS_BTN_1 )->keyCode = SDL_BUTTON_LEFT;

	(( (*configuration) + AVOID_OUTWRITE )->descriptif) = "NULL";
	( (*configuration) + AVOID_OUTWRITE )->keyCode = NULL_TOUCHE;

	return 0;
}

int SDL_touches( uint8_t *keyboardState, configTouches_t *configuration ) {
	/*	fonction a apeller a chaque image afin de recuperer l'etat ( appuyer ou relacher ) a chaque image
		x et y ne servent uniquement a recuperer les coordonees de la souris */

	SDL_Event event;

	short i;

	while ( SDL_PollEvent(&event) ) {

		i = 0;

		switch( event.type ) {

			case SDL_QUIT:

				* ( keyboardState + QUITTER ) = PRESSED;
				break;

			case SDL_KEYDOWN:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES_REEL )
					i++;

				*( keyboardState + i ) = PRESSED;
				break;

			case SDL_KEYUP:

				while ( event.key.keysym.sym != ( configuration + i)->keyCode && i < NB_TOUCHES_REEL )
					i++;

				*( keyboardState + i ) = RELEASED;
				break;

			case SDL_MOUSEBUTTONDOWN:

				while ( event.button.button != ( configuration + i)->keyCode && i < NB_TOUCHES_REEL )
					i++;

				*( keyboardState + i ) = PRESSED;
				break;

			case SDL_MOUSEBUTTONUP:

				while ( event.button.button != ( configuration + i)->keyCode && i < NB_TOUCHES_REEL )
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

void SDL_coord_souris ( uint32_t *x, uint32_t *y ) {

	SDL_GetMouseState( x, y);
}

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration ) {
/* fermeture propre du module touches pour SDL */

	free( *keyboardState );
	free(*configuration);

	return 0;
}
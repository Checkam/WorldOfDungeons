#include <stdlib.h>
#include <stdio.h>

#include <touches.h>
static void SDL_touche_default ( configTouches_t **configuration );

#include <chemin.h>
#include <json.h>

#include <SDL2/SDL.h>

int SDL_init_touches( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* permet d'allouer les zone memoire necessaire au bon fonctionnement du module touches */

	uint16_t i;
	int16_t keyID = -1, value;
	char descr[LONGUEUR_MAX_DESCRIPTIF];
	uint8_t continuer = 1;

	*keyboardState = malloc( sizeof( short ) * NB_TOUCHES );
	*configuration = malloc( sizeof( configTouches_t) * NB_TOUCHES);

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		* ( (*keyboardState) + i ) = RELEASED;
	}

	FILE *config = open_json("data/data/", "configuration_touches", "r");

	if ( config ) {

		char *ligne;

		fstart(config);

		extract_json_obj( config, &ligne);

		for ( i = 0 ; i < NB_TOUCHES_REEL && continuer ; i++ ) {

			read_json_obj( ligne, "keyID", &keyID, 'd');
			read_json_obj( ligne, "value", &value, 'd');
			read_json_obj( ligne, "descr", &descr, 's');

			if ( keyID == -1 ) {

				printf("Erreur : fichier de sauvegarde des touches corrompu ... ");
				continuer = 0;
			} else {

				strcpy( (( (*configuration) + keyID )->descriptif), descr);
				( (*configuration) + keyID )->keyCode = value;

				keyID = -1;
			}
		}
	}

	if ( !continuer || !config ) {

		printf("Restauration des touches par default ...\n");

		SDL_touche_default( configuration );
	}

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

void SDL_coord_souris ( int32_t *x, int32_t *y ) {

	SDL_GetMouseState( x, y);
}

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration ) {
/* fermeture propre du module touches pour SDL */

	free( *keyboardState );
	free(*configuration);

	return 0;
}

static void SDL_touche_default ( configTouches_t **configuration ) {

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
}
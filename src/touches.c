#include <stdlib.h>
#include <stdio.h>

#include <touches.h>
static void SDL_touche_default ( configTouches_t **configuration );	

#include <json.h>

#include <SDL2/SDL.h>

int SDL_init_touches( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* permet d'allouer les zone memoire necessaire au bon fonctionnement du module touches */

	int i;
	int16_t keyID = -1;
	uint32_t value;
	char descr[LONGUEUR_MAX_DESCRIPTIF];
	uint8_t continuer = 1;

	/* allocation de la memoire necessaire au fonctionnement du module */

	*keyboardState = malloc( sizeof( short ) * NB_TOUCHES );
	*configuration = malloc( sizeof( configTouches_t) * NB_TOUCHES);

	for ( i = 0 ; i < NB_TOUCHES ; i++ ) {

		((*configuration) + i)->descriptif = malloc( sizeof(char) * LONGUEUR_MAX_DESCRIPTIF);
		* ( (*keyboardState) + i ) = RELEASED;
	}

	* (( *keyboardState) + SOURIS_ROUE_BAS ) = 0;
	* (( *keyboardState) + SOURIS_ROUE_HAUT ) = 0;

	FILE *config = open_json("data/data/", "configuration_touches", "r");

	/* si des touches ont deja ete configure sur cette ordianteur alors on les charges */

	if ( config ) {

		char *ligne;

		fstart(config);

		for ( i = 0 ; i < NB_TOUCHES_REEL && continuer ; i++ ) {

			extract_json_obj( config, &ligne);

			read_json_obj( ligne, "keyID", &keyID, "d16");
			read_json_obj( ligne, "value", &value, "u");
			read_json_obj( ligne, "descr", descr, "s");

			free(ligne);

			if ( keyID < 0 || keyID >= NB_TOUCHES_REEL ) { /* evitement d un debordement memoire */

				printf("Erreur : fichier de sauvegarde des touches corrompu ... ");
				continuer = 0;
			} else {

				strcpy( (( (*configuration) + keyID )->descriptif), descr);
				( (*configuration) + keyID )->keyCode = value;

				keyID = -1;
			}
		}

		fclose(config);
	}

	/* si les touches n ont pas ete configure sur ce pc ou qu il a ete modifier alors on charge les touches par default */

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

			case SDL_MOUSEWHEEL:

				if ( event.wheel.y == 1)
					(*( keyboardState + SOURIS_ROUE_HAUT )) ++;
				else
					(*( keyboardState + SOURIS_ROUE_BAS )) ++;
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

void SDL_reset_wheel_state( uint8_t *keyboardState ) {
	/* doit etre apeller a chaque tour de la boucle pour remettre la roue a 0 */

	(*( keyboardState + SOURIS_ROUE_HAUT )) = 0;
	(*( keyboardState + SOURIS_ROUE_BAS )) = 0;
}

int8_t SDL_wheel_state( uint8_t *keyboardState ) {
	/* renvoie le TOTAL ( peut etre entre -127 et +128 ) du nombre de tour effectuer par l'utilasateur depuis le dernier apelle de SDL_reset_wheel_state */

	return (*( keyboardState + SOURIS_ROUE_HAUT )) - (*( keyboardState + SOURIS_ROUE_BAS ));
}

void SDL_coord_souris ( int32_t *x, int32_t *y ) {
	/* met les coordonees de la souris dans x et y */

	SDL_GetMouseState( x, y);
}

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration ) {
	/* fermeture propre du module touches pour SDL */

	/*	Sauvegarde des touches utilisateurs */

	int i;

	FILE *sauv = open_json("data/data/", "configuration_touches", "w");

	if ( sauv ) {

		int temp;

		/* ecriture des touches dans un fichier json */

		for ( i = 0 ; i < NB_TOUCHES_REEL ; i++ ) {

			open_json_obj( sauv );

			write_json( sauv, "keyID", &i, "d");

			temp = ( (*configuration) + i )->keyCode;

			write_json( sauv, "value", &temp, "d");
			write_json( sauv, "descr", ( (*configuration) + i )->descriptif, "s");

			close_json_obj( sauv );

		}

		fclose(sauv);

	} else
		printf("Erreur : impossible de créer un fichier de sauvegarde pour les touches\n");

	/* liberation de la memoire */

	for ( i = 0 ; i < NB_TOUCHES ; i++ )
		free(( (*configuration) + i )->descriptif);

	free( *keyboardState );
	free( *configuration );

	return 0;
}

static void SDL_touche_default ( configTouches_t **configuration ) {

	strcpy(( (*configuration) + QUITTER )->descriptif, "quitter");
	( (*configuration) + QUITTER )->keyCode = NULL_TOUCHE;

	strcpy(( (*configuration) + AVANCER )->descriptif, "avancer");
	( (*configuration) + AVANCER )->keyCode = SDLK_z;

	strcpy(( (*configuration) + RECULER )->descriptif, "reculer");
	( (*configuration) + RECULER )->keyCode = SDLK_s;

	strcpy(( (*configuration) + GAUCHE )->descriptif, "gauche");
	( (*configuration) + GAUCHE )->keyCode = SDLK_q;

	strcpy(( (*configuration) + DROITE )->descriptif, "droite");
	( (*configuration) + DROITE )->keyCode = SDLK_d;

	strcpy(( (*configuration) + SPACE )->descriptif, "sauter");
	( (*configuration) + SPACE )->keyCode = SDLK_SPACE;

	strcpy(( (*configuration) + G )->descriptif, "g");
	( (*configuration) + G )->keyCode = SDLK_g;

	strcpy(( (*configuration) + X )->descriptif, "x");
	( (*configuration) + X )->keyCode = SDLK_x;

	strcpy(( (*configuration) + SHIFT )->descriptif, "shift");
	( (*configuration) + SHIFT )->keyCode = SDLK_LSHIFT;

	strcpy(( (*configuration) + ESCAPE )->descriptif, "escape");
	( (*configuration) + ESCAPE )->keyCode = SDLK_ESCAPE;

	strcpy(( (*configuration) + SOURIS_BTN_1 )->descriptif, "souris_gauche");
	( (*configuration) + SOURIS_BTN_1 )->keyCode = SDL_BUTTON_LEFT;

	strcpy(( (*configuration) + SOURIS_BTN_2 )->descriptif, "souris_droit");
	( (*configuration) + SOURIS_BTN_2 )->keyCode = SDL_BUTTON_RIGHT;

	strcpy(( (*configuration) + SOURIS_ROUE_HAUT )->descriptif, "souris_roue_haut");
	( (*configuration) + SOURIS_ROUE_HAUT )->keyCode = NULL_TOUCHE;

	strcpy(( (*configuration) + SOURIS_ROUE_BAS )->descriptif, "souris_roue_bas");
	( (*configuration) + SOURIS_ROUE_BAS )->keyCode = NULL_TOUCHE;

	strcpy(( (*configuration) + AVOID_OUTWRITE )->descriptif, "NULL");
	( (*configuration) + AVOID_OUTWRITE )->keyCode = NULL_TOUCHE;
}
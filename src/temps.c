#define SECONDE 1000

#include <SDL/SDL2.h>
#include <time.h>

/**/#include <stdio.h>

double FPS ( const Uint8 FPS_CIBLE, const Uint16 tempsImageBase, const Uint16 tempsImage, const Uint8 pause ) {

	/* init var */

	static Uint16 nbImage = 0;
	static Uint32 debutImage = SDL_GetTicks(), debutSeconde;
	Uint32 tempsMS = 0, tempsS = 0;
	struct timespec vsleep;

	double compensation;

	/* debut controle */

	if ( tempsMS > SECONDE ) {

		debutSeconde = SDL_GetTicks();

		tempsMS = 0;
		tempsS++;

		nbImage = 0
		tempsSeconde = SDL_GetTicks();
		tempsSeconde = 0;
	}

	Uint_32 cible = tempsImage * nbImage

	if ( SDL_GetTicks() - debutSeconde > cible ) {

		compensation = ( SDL_GetTicks() - debutSeconde + cible ) / tempsImage - nbImage;

		nbImage += compensation;

	} else {

	 // temps d'attente entre chaque image si le processeur a finit l'image avant le temps impartit par tempsImage

		vsleep.tv_nsec = ( tempsImage - ( SDL_GetTicks() - debutImage ) - 1 ) * 1000;
		nanosleep(&vsleep, NULL);

		while ( SDL_GetTicks() - debutImage < tempsImage );

		compensation = (SDL_GetTicks() - debutImage) / (double)tempsImageBase;

		nbImage++;

	// fin du calcul de l'image

	}

	tempsMS += SDL_GetTicks() - debutImage;

	debutImage = SDL_GetTicks();

	return compensation;
}
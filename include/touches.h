#define NB_TOUCHES 8
#define LONGUEUR_MAX_DESCRIPTIF 20 /* longueur max en caractere du descriptif de la touche */
#define NULL_TOUCHE 65000

#define PRESSED 1
#define RELEASED 0

#define QUITTER 0
#define AVANCER 1
#define RECULER 2
#define GAUCHE 3
#define DROITE 4

/*	quiter
	avancer
	reculer
	gauche
	droite
	casser
	poser
	sauter
*/

typedef struct configTouches_s {

	uint16_t keyCode;
	char *descriptif;
} configTouches_t

int init_touches( Uint16 *keybordState, Uint16 *configuration );

int TERM_touches ();
int SDL_touches (Uint16 *keybordStat);

int SDL_exit_touches ( Uint16 *configuration );

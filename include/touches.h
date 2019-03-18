#ifndef __TOUCHES_H__
#define __TOUCHES_H__

#include <stdint.h>

#define NB_TOUCHES 8
#define NB_TOUCHES_REEL 7
#define LONGUEUR_MAX_DESCRIPTIF 20 /* longueur max en caractere du descriptif de la touche */
#define NULL_TOUCHE 64999


#define PRESSED 1
#define RELEASED 0


#define QUITTER 0	/* Quand on appuye sur la croix en haut a droite */

#define AVANCER 1

#define RECULER 2

#define GAUCHE 3

#define DROITE 4

#define ESCAPE 5	/* la touche escape en haut a gauche */

#define SOURIS_BTN_1 6 /* click gauche */
#define SOURIS_GAUCHE 6

#define AVOID_OUTWRITE 7 /* DOIT etre le dernier */

typedef struct configTouches_s {

	uint16_t keyCode;
	char *descriptif;
} configTouches_t;

int SDL_init_touches( uint8_t **keybordState, configTouches_t **configuration );

int SDL_touches ( uint8_t *keybordState, configTouches_t *configuration);
uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche );
void SDL_coord_souris ( uint16_t *x, uint16_t *y );

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration );

#endif

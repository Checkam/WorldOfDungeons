#ifndef __TOUCHES_H__
#define __TOUCHES_H__

#include <stdint.h>

#define NB_TOUCHES 6
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

typedef struct configTouches_s {

	uint16_t keyCode;
	char *descriptif;
} configTouches_t;

int SDL_init_touches( uint8_t **keybordState, configTouches_t **configuration );

int SDL_touches ( uint8_t *keybordState, configTouches_t *configuration);
uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche );

int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration );

#endif

#ifndef __TOUCHES_H__
#define __TOUCHES_H__

#include <stdint.h>

#define NB_TOUCHES 10
#define NB_TOUCHES_REEL 9
#define LONGUEUR_MAX_DESCRIPTIF 20 /* longueur max en caractere du descriptif de la touche */
#define NULL_TOUCHE 4199999


#define PRESSED 1
#define RELEASED 0


#define QUITTER 0	/* Quand on appuye sur la croix en haut a droite */

#define AVANCER 1

#define RECULER 2

#define GAUCHE 3

#define DROITE 4

#define SPACE 5
#define SAUTER 5

#define SHIFT 6

#define ESCAPE 7	/* la touche escape en haut a gauche */

#define SOURIS_BTN_1 8 /* click gauche */
#define SOURIS_GAUCHE 8

#define AVOID_OUTWRITE 9 /* DOIT etre le dernier */

typedef struct configTouches_s {

	uint32_t keyCode;
	char *descriptif;
} configTouches_t;

/*	initialisation du module touche
	doit etre apeler une unique fois dans le programme */
int SDL_init_touches( uint8_t **keybordState, configTouches_t **configuration );


/*	recupere l etat du clavier et de la souris
	doit etre apeler dans une boucle avant les 2 fonctions suivantes*/
int SDL_touches ( uint8_t *keybordState, configTouches_t *configuration);

/* 	recupere l etat d une touche
	voir les define ci dessus pour les touches disponible */
uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche );

/*	met les coordonees de la souris dans x et y */
void SDL_coord_souris ( int32_t *x, int32_t *y );


/*	doit etre apeler a la fin du programme pour une fermeture propre du module touche */
int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration );

/*static void SDL_touche_default ( configTouches_t **configuration );*/

#endif

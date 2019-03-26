#ifndef __TOUCHES_H__
#define __TOUCHES_H__

#include <stdint.h>

#define NB_TOUCHES 13
#define NB_TOUCHES_REEL 12
#define LONGUEUR_MAX_DESCRIPTIF 20 /* longueur max en caractere du descriptif de la touche */
#define NULL_TOUCHE 4199999


#define PRESSED 1
#define RELEASED 0

/****************************************************************************************
 * 			LES TOUCHES QUI PEUVENT ETRE UTILISER SONT TOUTES CI DESSOUS				*
 ****************************************************************************************/

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

#define SOURIS_BTN_2 9
#define SOURIS_DROIT 9

#define SOURIS_ROUE_HAUT 10

#define SOURIS_ROUE_BAS 11

#define AVOID_OUTWRITE 12 /* DOIT etre le dernier et ne doit pas etre touché */

typedef struct configTouches_s {

	uint32_t keyCode;
	char *descriptif;
} configTouches_t;

/************************************************************************************************************************************
 * 														MODULE TOUCHE																*
 * 										Il vaut mieux aller voir le test du module touche pour										*
 * 												comprendre les fonctions si dessous													*
 ************************************************************************************************************************************/

/************************************************* FONCTION A APELLE UNIQUE *********************************************************/

/*	initialisation du module touche
	doit etre apeler une unique fois dans le programme */
int SDL_init_touches( uint8_t **keybordState, configTouches_t **configuration );

/*	doit etre apeler a la fin du programme pour une fermeture propre du module touche */
int SDL_exit_touches ( uint8_t **keyboardState, configTouches_t **configuration );





/******************** FONCTION A APLLER DANS UNE BOUCLE NECESSAIRE AU BON FONCTIONNEMENT DU MODULE TOUCHE ***************************/

/*	recupere l etat du clavier et de la souris
	doit etre apeler dans une boucle avant les fonctions suivantes*/
int SDL_touches ( uint8_t *keybordState, configTouches_t *configuration);

/* doit etre apeller a chaque tour de la boucle pour remettre la roue a 0 */
void SDL_reset_wheel_state( uint8_t *keyboardState );





/************************************* FONCTION INDIQUANT L'ETAT DU CLAVIER ET DE LA SOURIS ******************************************/

/* 	recupere l etat d une touche
	voir les define ci dessus pour les touches disponible */
uint8_t SDL_touche_appuyer ( uint8_t *keyboardState, uint16_t touche );

/* renvoie le TOTAL ( peut etre entre -127 et +128 ) du nombre de tour effectuer par l'utilasateur depuis le dernier apelle de SDL_reset_wheel_state. si negatif la roue est tournée vers le bas si positif la roue est tournée vers le haut */
int8_t SDL_wheel_state( uint8_t *keyboardState );

/*	met les coordonees de la souris dans x et y */
void SDL_coord_souris ( int32_t *x, int32_t *y );

#endif

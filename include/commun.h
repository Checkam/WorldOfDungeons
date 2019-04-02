#ifndef __COMMUN_H__
#define __COMMUN_H__

#define NB_BLOCK_WIDTH 80
#define NB_BLOCK_HEIGHT 45


int height_window;
int width_window;

int width_block_sdl;
int height_block_sdl;

#define MAX 200 /* Height tab */
#define HAUTEUR_MINIMUN 50

#define SIZE ((width_window / width_block_sdl))   /* Width of screen */
#define MAX_SCREEN (height_window / height_block_sdl)  /* Heigth of screen */

int SEED;

typedef enum e_collision_direction
{
    DIRECT_DROITE_COLLI,
    DIRECT_GAUCHE_COLLI,
    DIRECT_HAUT_COLLI,
    DIRECT_BAS_COLLI
}t_collision_direction;

#endif

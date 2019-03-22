#ifndef __COMMUN_H__
#define __COMMUN_H__

int height_window;
int width_window;

#define width_block_sdl 25
#define height_block_sdl 25

#define MAX 100 /* Height tab */

#define SIZE (width_window / width_block_sdl)    /* Width of screen */
#define MAX_SCREEN (height_window / height_block_sdl)  /* Heigth of screen */

int SEED;

typedef enum
{
    DIRECT_DROITE_COLLI,
    DIRECT_GAUCHE_COLLI,
    DIRECT_HAUT_COLLI,
    DIRECT_BAS_COLLI
}t_collision_direction;

#endif

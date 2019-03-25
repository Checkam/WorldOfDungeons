#ifndef __ITEM_H__
#define __ITEM_H__

#include <block.h>
#include <liste.h>
#include <stdint.h>

typedef enum {

    I_TERRE, I_PIERRE_CASSEE, I_SABLE,
    I_BOIS, I_POUSSE_ARBRE, I_POMME,
    I_END
} t_item;

typedef struct item_type_s {

    uint16_t id;
    char *nomItem;

    t_block_type *posable; /* si l item peut etre poser, alors non NULL */

    SDL_Texture *texture;

} t_item_type;

typedef struct liste_drop_s {

    t_item item;
    uint8_t nombre;
    uint32_t besoin;
    uint16_t pourMille;

} t_liste_drop;

typedef struct block_drop_s {

    t_block_type id; /* un block peut drop plusieurs items*/

    t_liste_drop **drop;

} t_block_drop;

#endif
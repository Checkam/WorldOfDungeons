#ifndef __ITEM_H__
#define __ITEM_H__

#include <block.h>

typedef enum {
    TERRE = 0, PIERRE_CASSER, SABLE,
    BOIS = 50
}

typedef struct item_type_s {

    uint16_t id;
    char *nomItem;

    t_block_type *posable; /* si l item peut etre poser, alors non NULL */

    SDL_Texture *texture;

} t_item_type;

#endif
#ifndef __INVENTAIRE_H__
#define __INVENTAIRE_H__

#include <item.h>
#include <stdlib.h>

typedef struct inventaire_item_s {
    
    t_item_type *item;
    uint16_t durabilite;
} t_inventaire_item;

typedef struct inventaire_s {

    t_inventaire_item *inventaire;
    uint16_t nbItem;
} t_inventaire;

uint8_t alloc_item(t_inventaire *inventaire, const uint16_t nbItem );
void free_inventaire( t_inventaire *inventaire );

#endif
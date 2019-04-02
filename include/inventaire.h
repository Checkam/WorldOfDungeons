#ifndef __INVENTAIRE_H__
#define __INVENTAIRE_H__

#include <assert.h>

#include <item.h>
#include <stdlib.h>
#include <liste.h>

t_item_type *tabItem = NULL;

typedef struct inventaire_item_s {
    
    t_item_type *item;
    uint16_t stack;
    uint16_t durabilite;
} t_inventaire_item;

typedef struct inventaire_s {

    t_inventaire_item *inventaire;
    uint16_t nbItem;
    uint16_t nbItemMax;
} t_inventaire;

t_inventaire *create_inventaire();

uint8_t alloc_item(t_inventaire *inventaire, const uint16_t nbItem );

uint16_t slot_libre ( t_inventaire *inventaire );
void ajout_item_dans_inventaire( t_inventaire *inventaire, const t_item item, const uint16_t nb );

void free_inventaire( t_inventaire *inventaire );

#endif
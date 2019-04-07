#ifndef __INVENTAIRE_H__
#define __INVENTAIRE_H__

#include <SDL2/SDL.h>

#include <assert.h>

#include <item.h>
#include <stdlib.h>
#include <liste.h>
#include <chemin.h>

#define DEFAULT_SIZE_IMG_W 150
#define DEFAULT_SIZE_IMG_H 150

#define DEFAULT_SIZE_SCREEN_W 1920
#define DEFAULT_SIZE_SCREEN_H 1080 /* NE PAS CHANGER LES CONSTANTES */

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

uint16_t HEIGHT;
uint16_t WIDTH;

uint16_t scaleH;
uint16_t scaleW;

float uiScale;

void inventaire_init( SDL_Renderer *renderer );
t_inventaire *create_inventaire();

void alloc_item(t_inventaire *inventaire, const uint16_t nbItem );

void slot_libre ( t_inventaire *inventaire );
void ajout_item_dans_inventaire( t_inventaire *inventaire, t_liste *listeItem );
void inventaire_changer_constante ( const uint8_t nbinventaire );

void afficher_inventaire ( t_inventaire *inventaire );
void SDL_afficher_barre_action ( SDL_Renderer *renderer, t_inventaire *inventaire, const int8_t scroll );

void free_inventaire( t_inventaire *inventaire );

#endif
#ifndef __INVENTAIRE_H__
#define __INVENTAIRE_H__

#include <SDL2/SDL.h>

#include <assert.h>

#include <item.h>
#include <stdlib.h>
#include <liste.h>
#include <chemin.h>

#define DEFAULT_SIZE_SCREEN_W 1920.0
#define DEFAULT_SIZE_SCREEN_H 1080.0 /* NE PAS CHANGER LES CONSTANTES */




/* ----- STRUCTURE ----- */

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

typedef struct enr_inventaire_s {

    int64_t x;
    int32_t y;
    t_inventaire *inventaire;
} t_enr_inventaire;




/* ----- VARIABLES ------ */

uint16_t HEIGHT;
uint16_t WIDTH;

float scaleH;
float scaleW;

float uiScale;




/* ----- FONCTIONS ------ */

/* initialisation du module inventaire */
void inventaire_init( SDL_Renderer *renderer );

/* renvoie un inventaire ne pouvant pas contenir d'item. alloc_item devrait etre apellé apres cette fonction */
t_inventaire *create_inventaire();

/* alloue nbItem place dans l'inventaire. peut etre apeller meme si inventaire a deja ete passer dans alloc_item, dans le cas d'un ré-apelle garde les items deja présent */
void alloc_item(t_inventaire *inventaire, const uint16_t nbItem );



/* ajoute le maximum d'item possible contenu dans la liste dans l'inventaire */
void ajout_item_dans_inventaire( t_inventaire *inventaire, t_liste *listeItem );

/* si une constante change ( taille de la fenetre, nb d'item dans la barre d'action ), doit etre apeller. Ne PAS apeller a chaque image */
void inventaire_changer_constante ( const uint8_t nbinventaire );

/* affiche l'inventaire dans le terminal */
void afficher_inventaire ( t_inventaire *inventaire );

/* doit etre apeller uniquement lorsque le joueur veut poser un bloc. renvoie le bloc qui doit etre posé, AIR si il n'y a pas de bloc a posé */
t_materiaux poser_block ( t_inventaire *inventaire );

/* affiche la barre d'action. Ne doit pas etre apeller avec inventaire_afficher */
void SDL_afficher_barre_action ( SDL_Renderer *renderer, t_inventaire *inventaire, const int8_t scroll );

/* affiche l'inventaire en entier dans la fentre. Ne doit pas etre apeller avec SDL_afficher_barre_action */
void inventaire_afficher ( SDL_Renderer *renderer, t_inventaire *inventaire );




/* En cours de construction ... */
void inventaire_enregistrer ( const char *path, t_enr_inventaire *enr_inventaire );
void inventaire_recuperer ( const char *path, t_inventaire **inventaire, const int64_t x, const int32_t y );



/* permet une fermeture propre du module inventaire */
void free_inventaire( t_inventaire *inventaire );

#endif
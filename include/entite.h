#ifndef __ENTITE_H__
#define __ENTITE_H__
/**
 * \file entite.h
 * \brief Module contenant les primitives de gestion des entités.
 * \author GALBRUN Tibane
 * \date 13/03/2019
 * \version 0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <erreur.h>

/**
 * \enum t_entite_type
 * \brief Les différents types d'entités prédéfinis.
*/
typedef enum{
    JOUEUR,
    ZOMBIE,
    BOSS
}t_entite_type;

/**
 * \struct t_hitbox
 * \brief Contient la position et la taille de la hitbox.
*/
typedef struct s_hitbox
{
    int x,y;
    int l,h;
}t_hitbox;

/**
 * \struct t_entite
 * \brief Contient une entite et ses paramètres.
*/
typedef struct s_entite
{
    int id;
    char * name;
    long int xp;
    int mana, pv, faim;
    int mana_max, pv_max, faim_max;
    SDL_Texture * texture;
    t_hitbox hitbox;
    // Structure inventaire à rajouter
}t_entite;

/**
 * \enum t_action
 * \brief Les différentes actions possible par l'entité.
*/
typedef enum{
    IMMOBILE,
    DROITE,
    GAUCHE,
    DEVANT
}t_action;

/**
 * \struct t_t_a
 * \brief Contient la texture correspondant à une action.
*/
typedef struct s_t_a
{
    t_action action;
    SDL_Texture * texture;
}t_t_a;

/**
 * \struct t_lieu_t_a
 * \brief Contient le chemin de la texture correspondant à une action.
*/
typedef struct s_lieu_t_a
{
    t_action action;
    char * lieu;
}t_lieu_t_a;


/* Crée une entité avec des paramètres par défaut */
t_entite * creer_entite_defaut (char * name, t_hitbox hitbox, SDL_Texture * texture, t_entite_type type);
/* Crée une entité */
t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, t_hitbox hitbox);
/* Crée une hitbox */
t_hitbox creer_hitbox (int x, int y, int largeur, int longueur);
/* Détruit une entité */
t_erreur detruire_entite (t_entite * entite);
/* Initialise les textures d'une entité */
t_erreur init_texture_entite (t_entite * entite, t_entite_type type);

#endif
#ifndef __ENTITE_H__
#define __ENTITE_H__
/**
 * \file entite.h
 * \brief Module contenant les primitives de gestion des entités.
 * \author GALBRUN Tibane
 * \date 13/03/2019
 * \version 0.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <chemin.h>
#include <erreur.h>
#include <commun.h>


/******** PARTIE SPRITE ********/

#define H_SPRITE 1344
#define W_SPRITE 832

#define NB_LIGNES_SPRITE 21
#define NB_COLONNES_SPRITE 13

#define DECAL_H_SPRITE 12
#define DECAL_W_SPRITE 16

#define W_PART_SPRITE W_SPRITE/NB_COLONNES_SPRITE
#define H_PART_SPRITE H_SPRITE/NB_LIGNES_SPRITE

/**
 * \enum t_action
 * \brief Les différentes actions possible par l'entité.
*/
typedef enum{
    IMMOBILE,
    MARCHE_DROITE,
    MARCHE_GAUCHE,
    MARCHE_DEVANT,
    MARCHE_DERRIERE,
    ATTAQUE_GAUCHE,
    ATTAQUE_DROITE
}t_action;

/**
 * \struct t_anim_action
 * \brief Contient l'emplacement des textures associées à une action ainsi que la durée d'une animation.
*/
typedef struct s_anim_action
{
    t_action action;
    int ligne, nb_col;
    int temps_anim;
}t_anim_action;


/******** PARTIE ENTITE ********/

#define COEF_TAILLE_ENTITE 2.5
#define HAUTEUR_SAUT 9
#define VITESSE_DEPLACEMENT 5
#define ACCELERATION 1.5
#define POSX_ENT_SCREEN (width_window/2 - W_PART_SPRITE + width_block_sdl)
#define POSY_ENT_SCREEN (height_window/2 - H_PART_SPRITE)

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
 * \struct t_entite
 * \brief Contient une entite et ses paramètres.
*/
typedef struct s_entite
{
    int id;
    char * name; // Nom de l'entité
    long int xp; // XP gagné
    int mana, pv, faim; // Mana, PV et Faim courante
    int mana_max, pv_max, faim_max; // Mana, PV et Faim Max
    SDL_Rect hitbox; // Hitbox de l'entité
    SDL_Rect posEnt; // Position de l'entité sur la fenêtre
    SDL_Texture * texture; // Texture contenant toutes les animations de l'entité
    t_anim_action * texture_action; // Tableau contenant pour chaque action une animation et sa durée
    SDL_Rect texture_part; // Partie de la texture à afficher
    int col_act_prec; // Animation de l'action précèdente
    t_action act_pred; // Action précèdente
    int temp_dep; // Temps de départ de l'animation courante
    float velX, velY, accX, accY;
    // Structure inventaire à rajouter
}t_entite;


/****** Primitives des fonctions qui créent et suppriment les entités ******/

/* Crée une entité avec des paramètres par défaut */
t_entite * creer_entite_defaut (char * name, t_entite_type type, int x_dep, int y_dep);
/* Crée une entité */
t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, t_anim_action * t_a, int x_dep, int y_dep);
/* Détruit une entité */
t_erreur detruire_entite (t_entite * entite);
/* Initialise les textures d'une entité */
t_erreur init_texture_entite (t_entite * entite, t_entite_type type);


/****** Primitives des fonctions qui gèrent les sprites ******/

/* Initialise tous les sprites */
t_erreur Init_Sprite(SDL_Renderer * renderer);
/* Détruit tous les sprites */
t_erreur Quit_Sprite(void);
/* Crée la texture associée à l'image */
SDL_Texture * Create_Sprite (char * lieu, SDL_Renderer * renderer);
/* Charge l'animation sur le renderer */
t_erreur Charger_Anima (SDL_Renderer * renderer, t_entite * entite, t_action action);
/* Recherche l'indice d'une action */
int Search_Action (t_anim_action * t_a, t_action action);
/* Modifie le temps d'une animation associée à une action */
t_erreur Anim_Update (t_entite * entite, t_action action, int new_time);


/****** Primitives des fonctions qui gèrent les collisions des entités ainsi que la gravité ******/
t_erreur update_posY_entite(t_entite * entite, double coef_fps, int (*collision) (SDL_Rect,t_collision_direction));

/* Affiche les animations et modifie l'emplacement du joueur suivant les touches appuyées */
t_erreur Gestion_Entite (SDL_Renderer * renderer, t_entite * entite, uint8_t * ks, double coef_fps, int (*collision) (SDL_Rect,t_collision_direction));

#endif

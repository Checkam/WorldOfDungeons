/**
 * \file entite.c
 * \brief Module servant à gérer les entités.
 * \author GALBRUN Tibane
 * \date 13/03/2019
 * \version 0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <entite.h>
#include <erreur.h>
#include <chemin.h>
#include <outils_SDL.h>

/****** SPRITE TEXTURE ACTION ******/
t_s_a * t_a_joueur = {
    {IMMOBILE, 3, 1},
    {MARCHE_DROITE, 12, 9},
    {MARCHE_GAUCHE, 10, 9},
    {MARCHE_DEVANT, 9, 9},
    {MARCHE_DROITE, 11, 9}
};

/**
 * \fn t_entite * creer_entite_defaut (char * name, SDL_Rect hitbox, SDL_Texture * texture, t_entite_type type)
 * \brief Créer une entité avec des paramètres par défaut.
 * \param name Le nom de l'entité.
 * \param hitbox La hitbox de l'entité.
 * \param texture La texture de l'entité.
 * \param type Le type de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite_defaut (char * name, SDL_Rect hitbox, SDL_Texture * texture, t_entite_type type)
{
    if (!texture) return NULL;
    switch (type){
        case JOUEUR : return creer_entite((name) ? name : "PLAYER", 20, 20, 10, 10, texture, hitbox);
        case ZOMBIE : return creer_entite((name) ? name : "ZOMBIE", 0, 0, 10, 10, texture, hitbox);
        case BOSS : return creer_entite((name) ? name : "BOSS", 50, 50, 30, 30, texture, hitbox);
    }
    return NULL;
}

/**
 * \fn t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, SDL_Rect hitbox, t_s_a * t_a)
 * \brief Créer une entité.
 * \param name Le nom de l'entité.
 * \param mana Le mana de départ de l'entité.
 * \param mana_max Le mana max que peut avoir l'entité.
 * \param pv Les pv de départ de l'entité.
 * \param pv_max Les pv max de l'entité.
 * \param texture La texture de l'entité.
 * \param hitbox La hitbox de l'entité.
 * \param t_a Emplacement des textures liées à une action.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, SDL_Rect hitbox, t_s_a * t_a)
{
    if (!texture || !name) return NULL;
    if (mana > mana_max || pv > pv_max) {mana = mana_max; pv = pv_max;};

    t_entite * entite = malloc(sizeof(t_entite));
    entite->id = sizeof(*name);
    entite->name = name;
    entite->xp = 0;
    entite->faim = entite->faim_max = 10;
    entite->mana = mana;
    entite->mana_max = mana_max;
    entite->pv = pv;
    entite->pv_max = pv_max;
    entite->texture = texture;
    entite->hitbox = hitbox;

    return entite;
}

/**
 * \fn SDL_Rect creer_hitbox (int x, int y, int largeur, int hauteur)
 * \brief Créer une hitbox.
 * \param x La coordonnée en x de départ.
 * \param y La coordonnée en y de départ.
 * \param largeur La largeur de la hitbox.
 * \param hauteur La hauteur de la hitbox.
 * \return Un pointeur sur l'entité créée.
*/
SDL_Rect creer_hitbox (int x, int y, int largeur, int hauteur)
{
    SDL_Rect hit = {x,y,largeur,hauteur};
    return hit;
}

/**
 * \fn t_erreur detruire_entite (t_entite * entite)
 * \brief Détruit une entité.
 * \param entite L'entité à détruire.
 * \return Une erreur s'il y en a une.
*/
t_erreur detruire_entite (t_entite * entite)
{
    if (!entite) return PTR_NULL;
    free(entite);
    return OK;
}
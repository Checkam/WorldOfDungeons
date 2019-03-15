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

t_s_a t_a_joueur[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9},
    {MARCHE_GAUCHE, 10, 9},
    {MARCHE_DERRIERE, 9, 9},
    {MARCHE_DEVANT, 11, 9},
    {IMMOBILE, 3, 1}
};

t_s_a t_a_zombie[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9},
    {MARCHE_GAUCHE, 10, 9},
    {MARCHE_DERRIERE, 9, 9},
    {MARCHE_DEVANT, 11, 9},
    {ATTAQUE_GAUCHE, 14, 6},
    {ATTAQUE_DROITE, 16, 6},
    {IMMOBILE, 3, 1}
};

t_s_a t_a_boss[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9},
    {MARCHE_GAUCHE, 10, 9},
    {MARCHE_DERRIERE, 9, 9},
    {MARCHE_DEVANT, 11, 9},
    {ATTAQUE_GAUCHE, 14, 6},
    {ATTAQUE_DROITE, 16, 6},
    {IMMOBILE, 3, 1}
};

/****** FONCTION GESTION ENTITE ******/

/**
 * \fn t_entite * creer_entite_defaut (char * name, SDL_Texture * texture, t_entite_type type)
 * \brief Créer une entité avec des paramètres par défaut.
 * \param name Le nom de l'entité.
 * \param texture La texture de l'entité.
 * \param type Le type de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite_defaut (char * name, SDL_Texture * texture, t_entite_type type)
{
    if (!texture) return NULL;
    switch (type){
        case JOUEUR : return creer_entite((name) ? name : "PLAYER", 20, 20, 10, 10, texture, t_a_joueur);
        case ZOMBIE : return creer_entite((name) ? name : "ZOMBIE", 0, 0, 10, 10, texture, t_a_zombie);
        case BOSS : return creer_entite((name) ? name : "BOSS", 50, 50, 30, 30, texture, t_a_boss);
    }
    return NULL;
}

/**
 * \fn t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, t_s_a * t_a)
 * \brief Créer une entité.
 * \param name Le nom de l'entité.
 * \param mana Le mana de départ de l'entité.
 * \param mana_max Le mana max que peut avoir l'entité.
 * \param pv Les pv de départ de l'entité.
 * \param pv_max Les pv max de l'entité.
 * \param texture La texture de l'entité.
 * \param t_a Emplacement des textures liées à une action.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, t_s_a * t_a)
{
    if (!texture || !name || !t_a) return NULL;
    if (mana > mana_max || pv > pv_max) {mana = mana_max; pv = pv_max;};

    SDL_Rect Hit_ent = {0,t_a[0].ligne * H_PART_SPRITE + DECAL_H_SPRITE,W_PART_SPRITE,H_PART_SPRITE};

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
    entite->hitbox = Hit_ent;
    entite->texture_action = t_a;
    entite->col_act_prec = 0;
    entite->act_pred = IMMOBILE;

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


/****** FONCTION GESTION SPRITE ******/
SDL_Texture * Create_Sprite (char * lieu, SDL_Renderer * renderer)
{
    if (!renderer || !lieu) return NULL;

    char * chemin;
    creation_chemin(lieu,&chemin);

    SDL_Texture * texture;
    Create_IMG_Texture(renderer,chemin,&texture);
    free(chemin);

    return texture;
}

t_erreur Charger_Anima (SDL_Renderer * renderer, SDL_Rect fenetre, t_entite * entite, t_action action)
{
    if (!renderer || !entite) return PTR_NULL;

    int i = Search_Action(entite->texture_action, action);
    if (i == -1) return VALUE_ERROR;

    if (entite->col_act_prec == entite->texture_action[i].nb_col) entite->col_act_prec = 0;
    if (entite->act_pred != action) entite->col_act_prec = 0;

    entite->hitbox.y = (entite->texture_action[i].ligne - 1) * H_PART_SPRITE + DECAL_H_SPRITE;
    entite->hitbox.x = (entite->col_act_prec) * W_PART_SPRITE + DECAL_W_SPRITE;
    SDL_RenderCopy(renderer,entite->texture,&(entite->hitbox),&fenetre);

    (entite->col_act_prec)++;
    entite->act_pred = action;

    return OK;
}

int Search_Action (t_s_a * t_a, t_action action)
{
    if (!t_a) return -1;

    int i;
    for (i = 0; t_a[i].action != action && t_a[i].action != IMMOBILE; i++);

    return i;
}
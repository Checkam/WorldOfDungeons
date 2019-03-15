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

SDL_Texture * Textures_Joueur;
t_s_a t_a_joueur[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9, 100},
    {MARCHE_GAUCHE, 10, 9, 100},
    {MARCHE_DERRIERE, 11, 9, 100},
    {MARCHE_DEVANT, 9, 9, 100},
    {IMMOBILE, 3, 1, 50}
};

SDL_Texture * Textures_Zombie;
t_s_a t_a_zombie[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9, 100},
    {MARCHE_GAUCHE, 10, 9, 100},
    {MARCHE_DERRIERE, 11, 9, 100},
    {MARCHE_DEVANT, 9, 9, 100},
    {ATTAQUE_GAUCHE, 14, 6, 100},
    {ATTAQUE_DROITE, 16, 6, 100},
    {IMMOBILE, 3, 1, 100}
};

SDL_Texture * Textures_Boss;
t_s_a t_a_boss[NB_LIGNES_SPRITE] = {
    {MARCHE_DROITE, 12, 9, 100},
    {MARCHE_GAUCHE, 10, 9, 100},
    {MARCHE_DERRIERE, 11, 9, 100},
    {MARCHE_DEVANT, 9, 9, 100},
    {ATTAQUE_GAUCHE, 14, 6, 100},
    {ATTAQUE_DROITE, 16, 6, 100},
    {IMMOBILE, 3, 1, 50}
};

/****** FONCTION GESTION ENTITE ******/

/**
 * \fn t_entite * creer_entite_defaut (char * name, t_entite_type type)
 * \brief Créer une entité avec des paramètres par défaut.
 * \param name Le nom de l'entité.
 * \param type Le type de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite_defaut (char * name, t_entite_type type)
{
    switch (type){
        case JOUEUR : return creer_entite((name) ? name : "PLAYER", 20, 20, 10, 10, Textures_Joueur, t_a_joueur);
        case ZOMBIE : return creer_entite((name) ? name : "ZOMBIE", 0, 0, 10, 10, Textures_Zombie, t_a_zombie);
        case BOSS : return creer_entite((name) ? name : "BOSS", 50, 50, 30, 30, Textures_Boss, t_a_boss);
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

    SDL_Rect Hit_ent = {0 + DECAL_W_SPRITE,t_a[0].ligne * H_PART_SPRITE + DECAL_H_SPRITE,W_PART_SPRITE/2,H_PART_SPRITE/1.25};

    t_entite * entite = malloc(sizeof(t_entite));
    entite->id = sizeof(*name); // sizeof temporaire
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
    entite->temp_dep = SDL_GetTicks();

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

    /* On cherche l'action associée à l'entité */
    int i = Search_Action(entite->texture_action, action);
    if (i == -1) return VALUE_ERROR;

    /* On redémarre l'animation à zéro si on est arrivé au bout */
    if (entite->col_act_prec == entite->texture_action[i].nb_col) entite->col_act_prec = 0;
    /* On redémarre l'animation à 0 si l'action a changé */
    if (entite->act_pred != action) entite->col_act_prec = 0;

    /* On met à jour l'animation */
    entite->hitbox.y = (entite->texture_action[i].ligne - 1) * H_PART_SPRITE + DECAL_H_SPRITE;
    entite->hitbox.x = (entite->col_act_prec) * W_PART_SPRITE + DECAL_W_SPRITE;
    SDL_RenderCopy(renderer,entite->texture,&(entite->hitbox),&fenetre);

    /* On regarde si l'animation est finie avant de passer à la suivante */
    if (entite->act_pred == action && (SDL_GetTicks() - entite->temp_dep) >= entite->texture_action[i].temps_anim)
    {
        (entite->col_act_prec)++;
        entite->temp_dep = SDL_GetTicks();
    }
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

t_erreur Init_Sprite(SDL_Renderer * renderer)
{
    if (!renderer) return PTR_NULL;
    /* Création de la texture pour chaque SPRITE */
    Textures_Joueur = Create_Sprite("IMG/texture/entite/joueur/sprite_apoil.png",renderer);
    Textures_Zombie = Create_Sprite("IMG/texture/entite/zombie/sprite_apoil.png",renderer);
    Textures_Boss = Create_Sprite("IMG/texture/entite/boss/sprite_boss1.png",renderer);

    return OK;
}

t_erreur Quit_Sprite(void)
{
    /* Destruction des textures */
    SDL_DestroyTexture(Textures_Joueur);
    SDL_DestroyTexture(Textures_Zombie);
    SDL_DestroyTexture(Textures_Boss);
    return OK;
}
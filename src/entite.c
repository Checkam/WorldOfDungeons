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
#include <touches.h>

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
    {IMMOBILE, 3, 1, 50}
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

/****** FONCTIONS CREATION ET SUPPRESSION ENTITE ******/

/**
 * \fn t_entite * creer_entite_defaut (char * name, t_entite_type type)
 * \brief Créer une entité avec des paramètres par défaut.
 * \param name Le nom de l'entité.
 * \param type Le type de l'entité.
 * \param x_dep Coordonnée de départ de l'entité.
 * \param y_dep Coordonnée de départ de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite_defaut (char * name, t_entite_type type, int x_dep, int y_dep)
{
    switch (type){
        case JOUEUR : return creer_entite((name) ? name : "PLAYER", 20, 20, 10, 10, Textures_Joueur, t_a_joueur,x_dep,y_dep);
        case ZOMBIE : return creer_entite((name) ? name : "ZOMBIE", 0, 0, 10, 10, Textures_Zombie, t_a_zombie,x_dep,y_dep);
        case BOSS : return creer_entite((name) ? name : "BOSS", 50, 50, 30, 30, Textures_Boss, t_a_boss,x_dep,y_dep);
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
 * \param x_dep Coordonnée de départ de l'entité.
 * \param y_dep Coordonnée de départ de l'entité.
 * \return Un pointeur sur l'entité créée.
*/
t_entite * creer_entite (char * name, int mana, int mana_max, int pv, int pv_max, SDL_Texture * texture, t_s_a * t_a, int x_dep, int y_dep)
{
    if (!texture || !name || !t_a) return NULL;
    if (mana > mana_max || pv > pv_max) {mana = mana_max; pv = pv_max;};

    /* Endroit de départ dans le sprite pour animation */
    SDL_Rect sprite_part = {0 + DECAL_W_SPRITE,t_a[0].ligne * H_PART_SPRITE + DECAL_H_SPRITE,W_PART_SPRITE/2,H_PART_SPRITE/1.25};

    /* Initialisation de la taille de l'entité */
    SDL_Rect hit = {x_dep - sprite_part.w * 3,y_dep - sprite_part.h * 3,sprite_part.w * 3,sprite_part.h * 3};

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
    entite->texture_part = sprite_part;
    entite->texture_action = t_a;
    entite->col_act_prec = 0;
    entite->act_pred = IMMOBILE;
    entite->temp_dep = SDL_GetTicks();
    entite->hitbox = hit;

    return entite;
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


/****** FONCTIONS GESTION SPRITE ******/

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

t_erreur Charger_Anima (SDL_Renderer * renderer, t_entite * entite, t_action action)
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
    entite->texture_part.y = (entite->texture_action[i].ligne - 1) * H_PART_SPRITE + DECAL_H_SPRITE;
    entite->texture_part.x = (entite->col_act_prec) * W_PART_SPRITE + DECAL_W_SPRITE;
    SDL_RenderCopy(renderer,entite->texture,&(entite->texture_part),&(entite->hitbox));

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


/****** FONCTION GESTION COLLISION ENTITE ******/



/************** Focntion qui gère les déplacements et les animations de l'entité **************/
t_erreur Gestion_Entite (SDL_Renderer * renderer, t_entite * entite, uint8_t * ks)
{
    if (!renderer || !entite || !ks) return PTR_NULL;

    if (SDL_touche_appuyer( ks, AVANCER))
    {
        Charger_Anima(renderer,entite,MARCHE_DEVANT);
    }
    else if (SDL_touche_appuyer( ks, RECULER))
    {
        Charger_Anima(renderer,entite,MARCHE_DERRIERE);
    }
    else if (SDL_touche_appuyer( ks, DROITE))
    {
        entite->hitbox.x += 5;
        Charger_Anima(renderer,entite,MARCHE_DROITE);
    }
    else if (SDL_touche_appuyer( ks, GAUCHE))
    {
        entite->hitbox.x += -5;
        Charger_Anima(renderer,entite,MARCHE_GAUCHE);
    }
    else Charger_Anima(renderer,entite,IMMOBILE);

    if (SDL_touche_appuyer( ks, SAUTER))
    {
        entite->hitbox.y += -10;
    }

    return OK;
}
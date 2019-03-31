/**
 * \file ia.c
 * \brief Module de création + de gestion d'une IA
 * \author Jasmin GALBRUN
 * \date 31/03/2019
 * \version 1
*/

#include <entite.h>
#include <ia.h>
#include <erreur.h>
#include <commun.h>
#include <math.h>


/**
 * \fn t_action ia_jouer(t_entite * entite, t_entite * adversaire, uint16_t type)
 * \brief IA faisant jouer l'entite en fonction du comportement demandé
 * \param entite Entite voulant être jouer par l'IA
 * \param adversaire Adversaire dont on veut que l'IA tienne compte
 * \param type Comportement de l'IA
 * \return L'action que doit faire l'entite
*/
t_action ia_jouer(t_entite * entite, t_entite * adversaire, uint16_t type){
    /* Vérification */
    if(entite == NULL){
        return IMMOBILE;
    }

    if(type & IA_ALEATOIRE){
        double rnd = rand() / (double)RAND_MAX;
        if(rnd <= 0.95)
            return entite->act_pred;
        else
            return (rand() % SAUTER);
    }

    if(adversaire == NULL){
        return IMMOBILE;
    }

    if(type & IA_ATTAQUE){
        if(abs(entite->hitbox.x - adversaire->hitbox.x) <= 1 * entite->hitbox.w && abs(entite->hitbox.y - adversaire->hitbox.y) <= 1 * entite->hitbox.h){
            if(entite->hitbox.x - adversaire->hitbox.x < 0)
                return ATTAQUE_DROITE;
            else
                return ATTAQUE_GAUCHE;
        }
    }

    if(type & IA_FOCUS){
        if(entite->hitbox.x - adversaire->hitbox.x < 0)
            return MARCHE_DROITE;
        else
            return MARCHE_GAUCHE;
    }

    if(type & IA_FUITE){
        if(entite->hitbox.x - adversaire->hitbox.x < 0)
            return MARCHE_GAUCHE;
        else
            return MARCHE_DROITE;
    }

    return IMMOBILE;
}

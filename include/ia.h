/**
 * \file ia.h
 * \brief Module de création + de gestion d'une IA
 * \author Jasmin GALBRUN
 * \date 31/03/2019
 * \version 1
*/
#ifndef __IA_H__
#define __IA_H__

#include <entite.h>

/**
 * \enum t_type_ia
 * \brief Contient le type d'une IA
*/
typedef enum e_type_ia {
    IA_ALEATOIRE = 1,
    IA_ATTAQUE = 2,
    IA_FOCUS = 4,
    IA_FUITE = 8
} t_type_ia;


/*******************/
/* Jouer avec l'IA */
/*******************/
t_action ia_jouer(t_entite * entite, t_entite * adversaire, uint16_t type);

#endif
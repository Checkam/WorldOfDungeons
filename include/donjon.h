/**
 * \file donjon.h
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 13/03/2019
*/
#ifndef __DONJON_H__
#define __DONJON_H__

typedef struct s_salle_donjon{
    int x, y;
    int ** salle;
    int voisin[4]; //LEFT-TOP-RIGHT-BOTTOM
}t_salle_donjon;

#endif
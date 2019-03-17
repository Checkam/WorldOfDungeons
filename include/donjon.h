/**
 * \file donjon.h
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 17/03/2019
*/
#ifndef __DONJON_H__
#define __DONJON_H__

#include <erreur.h>
#include <liste.h>

typedef struct s_salle_donjon{
    int x, y;
    int ** structure;
    int voisin[4]; //LEFT-TOP-RIGHT-BOTTOM
}t_salle_donjon;

/* Primitives de création d'un donjon */
t_erreur donjon_creer(t_liste ** liste, int nb_salle);
t_erreur donjon_ajout_salle(t_liste * liste, int taille_donjon);
t_erreur donjon_creer_salle(t_salle_donjon ** salle, int x, int y);
int nb_voisin_salle(t_salle_donjon * salle);
t_erreur selection_voisin(t_salle_donjon * salle, int * choix);
int chercher_salle(t_liste *liste);
t_erreur update_voisin(t_liste * liste, int taille_donjon);



/* Primitives de destruction d'un donjon */
t_erreur donjon_detruire(t_liste **liste);
void donjon_detruire_salle(t_salle_donjon *salle);

#endif
#ifndef __LISTE_H__
#define __LISTE_H__
/**
 * \file liste.h
 * \brief Module des primitives de gestion de listes.
 * \author GALBRUN Tibane
 * \date 07/03/2019
 * \version 0.2
*/

#include <erreur.h>

/**
 * \struct t_element
 * \brief Element d'une liste.
*/
typedef struct element{
    void * elem;
    struct element * pred;
    struct element * succ;
} t_element;

/**
 * \struct t_liste
 * \brief Liste contenant des t_element.
*/
typedef struct s_liste{
    t_element * drapeau;
    t_element * ec;
}t_liste;

void init_liste(t_liste * p);
int liste_vide(t_liste * p);
int hors_liste(t_liste * p);
void en_tete(t_liste * p);
void en_queue(t_liste * p);
void precedent(t_liste * p);
void suivant(t_liste * p);
t_erreur valeur_elt(t_liste * p, void ** v);
t_erreur modif_elt(t_liste * p, void * v);
t_erreur oter_elt(t_liste * p, void (* effacer) (void *));
t_erreur ajout_droit(t_liste * p, void * v);
t_erreur ajout_gauche(t_liste * p, void * v);
int taille_liste(t_liste * p);
void detruire_liste(t_liste * p, void (* effacer) (void *));

char  * copie( char * cible , char * source , int n);
char * copie_cb (void * cible, void * source, int n);

#endif

/**
 * \file liste.c
 * \brief Module de gestion de listes.
 * \author GALBRUN Tibane
 * \date 07/03/2019
 * \version 0.2
*/

#include <stdlib.h>
#include <liste.h>
#include <erreur.h>

/**
 * \fn void init_liste(t_liste * p)
 * \brief Initialise une nouvelle liste.
 * \param p La liste à initialiser.
*/
void init_liste(t_liste * p){
    p->drapeau = malloc(sizeof(t_element));
    p->drapeau->pred = p->drapeau;
    p->drapeau->succ = p->drapeau;
    p->ec = p->drapeau;
}

/**
 * \fn int liste_vide(t_liste * p)
 * \brief Regarde si la liste est vide ou non.
 * \brief Renvoie vrai si la liste est vide, faux sinon.
 * \param p La liste à vérifier.
 * \return Un entier qui vaut vrai si la liste est vide.
*/
int liste_vide(t_liste * p){
    return (p->drapeau->succ == p->drapeau);
}

/**
 * \fn int hors_liste(t_liste * p)
 * \brief Regarde si on est en dehors de la liste ou non.
 * \brief Renvoie vrai si on est en dehors de la liste, faux sinon.
 * \param p La liste à vérifier.
 * \return Un entier qui vaut vrai si on est hors-liste.
*/
int hors_liste(t_liste * p){
    return (p->ec == p->drapeau);
}

/**
 * \fn void en_tete(t_liste * p)
 * \brief Place l'élèment courant sur la tete de liste.
 * \param p La liste où se trouve l'élèment courant à modifier.
*/
void en_tete(t_liste * p){
    if(!liste_vide(p))
        p->ec = p->drapeau->succ;
}

/**
 * \fn void en_queue(t_liste * p)
 * \brief Place l'élèment courant sur la queue de liste.
 * \param p La liste où se trouve l'élèment courant à modifier.
*/
void en_queue(t_liste * p){
    if(!liste_vide(p))
        p->ec = p->drapeau->pred;
}

/**
 * \fn void suivant(t_liste * p)
 * \brief Passe à l'élèment suivant s'il existe.
 * \param p La liste où se trouve l'élèment courant à modifier.
*/
void suivant(t_liste * p){
    if(!hors_liste(p))
        p->ec = p->ec->succ;
}

/**
 * \fn void precedent(t_liste * p)
 * \brief Passe à l'élèment précédent s'il existe.
 * \param p La liste où se trouve l'élèment courant à modifier.
*/
void precedent(t_liste * p){
    if(!hors_liste(p))
        p->ec = p->ec->pred;
}

/**
 * \fn t_erreur valeur_elt(t_liste * p, void ** v, int size_v)
 * \brief Récupère la valeur de l'élèment courant.
 * \param p La liste où se trouve l'élèment courant.
 * \param v L'endroit ou sauvegarder la valeur de l'élèment courant.
 * \param size_v La taille de l'élèment à récupérer.
 * \return Une erreur s'il y en a une.
*/
t_erreur valeur_elt(t_liste * p, void ** v, int size_v){
    if(!v) return PTR_NULL;
    if(!hors_liste(p)){
        copie_cb(*v, p->ec->elem, size_v);
    }
    else return PTR_VALUE_ERROR;
    return OK;
}

/**
 * \fn t_erreur modif_elt(t_liste * p, void * v)
 * \brief Modifie la valeur de l'élèment courant.
 * \param p La liste où se trouve l'élèment courant.
 * \param v La nouvelle valeur à enregistrer.
 * \return Une erreur s'il y en a une.
*/
t_erreur modif_elt(t_liste * p, void * v){
    if(!v) return PTR_NULL;
    if(!hors_liste(p)){
        p->ec->elem = v;
    }
    else return PTR_VALUE_ERROR;
    return OK;
}

/**
 * \fn t_erreur oter_elt(t_liste * p, void (* effacer) (void *))
 * \brief Supprime l'élèment courant.
 * \param p La liste où se trouve l'élèment courant.
 * \param effacer La fonction d'effacement de l'élèment courant.
 * \return Une erreur s'il y en a une.
*/
void * elem_pred = NULL;
t_erreur oter_elt(t_liste * p, void (* effacer) (void *)){
    if(!hors_liste(p)){
        if (p->ec->elem && p->ec->elem != elem_pred)
            effacer(p->ec->elem);
        elem_pred = p->ec->elem;
        p->ec->succ->pred = p->ec->pred;
        p->ec->pred->succ = p->ec->succ;
        t_element * tamp = p->ec;
        p->ec = tamp->pred;
        if (tamp)
            free(tamp);
    }else return PTR_VALUE_ERROR;
    return OK;
}

/**
 * \fn t_erreur ajout_droit(t_liste * p, void * v)
 * \brief Ajoute à droite de l'élèment courant la nouvelle valeur.
 * \param p La liste où se trouve l'élèment courant.
 * \param v La valeur à ajouter.
 * \return Une erreur s'il y en a une.
*/
t_erreur ajout_droit(t_liste * p, void * v){
    if(liste_vide(p) || !hors_liste(p)){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->elem = v;
        nouv->pred = p->ec;
        nouv->succ = p->ec->succ;
        p->ec->succ->pred = nouv;
        p->ec->succ = nouv;
        p->ec = nouv;
    }else return PTR_VALUE_ERROR;
    return OK;
}

/**
 * \fn t_erreur ajout_gauche(t_liste * p, void * v)
 * \brief Ajoute à gauche de l'élèment courant la nouvelle valeur.
 * \param p La liste où se trouve l'élèment courant.
 * \param v La valeur à ajouter.
 * \return Une erreur s'il y en a une.
*/
t_erreur ajout_gauche(t_liste * p, void * v){
    if(liste_vide(p) || !hors_liste(p)){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->elem = v;
        nouv->succ = p->ec;
        nouv->pred = p->ec->pred;
        p->ec->pred->succ = nouv;
        p->ec->pred = nouv;
        p->ec = nouv;
    }else return PTR_VALUE_ERROR;
    return OK;
}

/**
 * \fn int taille_liste(t_liste * p)
 * \brief Calcule la taille de la liste.
 * \param p La liste à mesurer.
 * \return La taille de la liste.
*/
int taille_liste(t_liste * p){
    int nb = 0;
    for(en_tete(p); !hors_liste(p); suivant(p)){
        nb++;
    }
    return nb;
}

/**
 * \fn void detruire_liste(t_liste * p, void (* effacer) (void *))
 * \brief Détruit la liste.
 * \param p La liste à détruire.
 * \param effacer La fonction d'effacement de l'élèment courant.
*/
void detruire_liste(t_liste * p, void (* effacer) (void *)){
    for(en_tete(p); !liste_vide(p); oter_elt(p,effacer), en_queue(p));
    if (p->drapeau)
        free(p->drapeau);
    elem_pred = NULL;
}

/**
 * \fn char * copie( char * cible , char * source , int n)
 * \brief Copie n octet de la source dans la cible.
 * \param cible L'endroit où copier.
 * \param source La source de la copie.
 * \param n Le nombre d'octet à copier.
 * \return L'adresse de la source.
*/
char * copie( char * cible , char * source , int n) 
{
    char * d = source ;
    while( n-- ) *cible++ = *source++ ;
    return d ;
}

/**
 * \fn char * copie_cb( char * cible , char * source , int n)
 * \brief Fonction de callback de la fonction copie.
 * \param cible L'endroit où copier.
 * \param source La source de la copie.
 * \param n Le nombre d'octet à copier.
 * \return L'adresse de la source.
*/
char * copie_cb (void * cible, void * source, int n)
{
    return (copie(cible,source,n));
}
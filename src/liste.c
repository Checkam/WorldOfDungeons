#include <stdlib.h>
#include <liste.h>

void init_liste(t_liste * p){
    p->drapeau = malloc(sizeof(t_element));
    p->drapeau->pred = p->drapeau;
    p->drapeau->succ = p->drapeau;
    p->ec = p->drapeau;
}

int liste_vide(t_liste * p){
    return (p->drapeau->succ == p->drapeau);
}

int hors_liste(t_liste * p){
    return (p->ec == p->drapeau);
}

void en_tete(t_liste * p){
    if(!liste_vide(p))
        p->ec = p->drapeau->succ;
}

void en_queue(t_liste * p){
    if(!liste_vide(p))
        p->ec = p->drapeau->pred;
}

void suivant(t_liste * p){
    if(!hors_liste(p))
        p->ec = p->ec->succ;
}

void precedent(t_liste * p){
    if(!hors_liste(p))
        p->ec = p->ec->pred;
}

void valeur_elt(t_liste * p, int** v){
    if(!hors_liste(p))
        *v = p->ec->tab;
}

void modif_elt(t_liste * p, int * v){
    if(!hors_liste(p))
        p->ec->tab = v;
}

void oter_elt(t_liste * p){
    if(!hors_liste(p)){
        free(p->ec->tab);
        p->ec->succ->pred = p->ec->pred;
        p->ec->pred->succ = p->ec->succ;
        t_element * tamp = p->ec;
        p->ec = tamp->pred;
        free(tamp);
    }
}

void ajout_droit(t_liste * p, int * v){
    if(liste_vide(p) || !hors_liste(p)){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->tab = v;
        nouv->pred = p->ec;
        nouv->succ = p->ec->succ;
        p->ec->succ->pred = nouv;
        p->ec->succ = nouv;
        p->ec = nouv;
    }
}

void ajout_gauche(t_liste * p, int * v){
    if(liste_vide(p) || !hors_liste(p)){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->tab = v;
        nouv->succ = p->ec;
        nouv->pred = p->ec->pred;
        p->ec->pred->succ = nouv;
        p->ec->pred = nouv;
        p->ec = nouv;
    }
}

int taille_liste(t_liste * p){
    int nb = 0;
    for(en_tete(p); !hors_liste(p); suivant(p)){
        nb++;
    }
    return nb;
}

void detruire_liste(t_liste * p){
    for(en_tete(p); !liste_vide(p); oter_elt(p), en_queue(p));
    free(p->drapeau);
}
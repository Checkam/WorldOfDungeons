#include <stdlib.h>

typedef struct element{
    int * tab;
    struct element * pred;
    struct element * succ;
} t_element;
t_element * drapeau;
t_element * ec;

void init_liste(){
    drapeau = malloc(sizeof(t_element));
    drapeau->pred = drapeau;
    drapeau->succ = drapeau;
    ec = drapeau;
}

int liste_vide(){
    return (drapeau->succ == drapeau);
}

int hors_liste(){
    return (ec == drapeau);
}

void en_tete(){
    if(!liste_vide())
        ec = drapeau->succ;
}

void en_queue(){
    if(!liste_vide())
        ec = drapeau->pred;
}

void suivant(){
    if(!hors_liste())
        ec = ec->succ;
}

void precedent(){
    if(!hors_liste())
        ec = ec->pred;
}

void valeur_elt(int** v){
    if(!hors_liste())
        *v = ec->tab;
}

void modif_elt(int * v){
    if(!hors_liste())
        ec->tab = v;
}

void oter_elt(){
    if(!hors_liste()){
        free(ec->tab);
        ec->succ->pred = ec->pred;
        ec->pred->succ = ec->succ;
        t_element * tamp = ec;
        ec = tamp->pred;
        free(tamp);
    }
}

void ajout_droit(int * v){
    if(liste_vide() || !hors_liste()){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->tab = v;
        nouv->pred = ec;
        nouv->succ = ec->succ;
        ec->succ->pred = nouv;
        ec->succ = nouv;
        ec = nouv;
    }
}

void ajout_gauche(int * v){
    if(liste_vide() || !hors_liste()){
        t_element * nouv = malloc(sizeof(t_element));
        nouv->tab = v;
        nouv->succ = ec;
        nouv->pred = ec->pred;
        ec->pred->succ = nouv;
        ec->pred = nouv;
        ec = nouv;
    }
}

int taille_liste(void){
    int nb = 0;
    for(en_tete(); !hors_liste(); suivant()){
        nb++;
    }
    return nb;
}

void detruire_liste(void){
    for(en_tete(); !liste_vide(); oter_elt(), en_queue());
    free(drapeau);
}
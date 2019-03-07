typedef struct element{
    int * tab;
    struct element * pred;
    struct element * succ;
} t_element;

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
void valeur_elt(t_liste * p, int**);
void modif_elt(t_liste * p, int*);
void oter_elt(t_liste * p);
void ajout_droit(t_liste * p, int*);
void ajout_gauche(t_liste * p, int*);
int taille_liste(t_liste * p);
void detruire_liste(t_liste * p);

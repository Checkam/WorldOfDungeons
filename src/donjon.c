/**
 * \file donjon.c
 * \brief Module de création + de gestion d'un donjon
 * \author Jasmin GALBRUN
 * \version 1
 * \date 26/03/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <chemin.h>
#include <SDL2/SDL.h>
#include <liste.h>
#include <erreur.h>
#include <commun.h>
#include <donjon.h>
#include <perlin.h>
#include <block.h>
#include <outils_SDL.h>
#include <stdbool.h>
#include <affichage.h>

#define DEPTH 5

/* Prototypes fonctions non accessible pour l'utilisateur */
static t_erreur donjon_creer_salle(t_salle_donjon ** salle, int x, int y, t_type_salle_donjon type);
static t_erreur donjon_ajout_salle(t_liste * donjon, int taille_donjon, t_entite * joueur);
static int nb_voisin_salle(t_salle_donjon * salle);
static t_erreur selection_voisin(t_salle_donjon * salle, int * choix);
static int chercher_salle(t_liste *donjon, t_entite * joueur);
static t_erreur update_voisin(t_liste * donjon, int taille_donjon);
static t_erreur donjon_creer_structure_salle(t_salle_donjon * salle);
static t_erreur tab_fenetre(t_liste * donjon, SDL_Rect pos_perso, t_liste ** tab_fenetre);
static void donjon_detruire_salle(t_salle_donjon *salle);
static t_erreur donjon_coord_depart(t_liste * donjon, t_salle_donjon ** salle_dep);
static t_erreur placer_salle_boss(t_liste * donjon);

/**
 * \fn t_erreur donjon_creer(t_donjon ** donjon, int nb_salle, t_entite * joueur)
 * \brief Fonction permettant de créer un donjon
 * \param liste Pointeur dans lequel sera stocké le donjon
 * \param nb_salle Nombre de salle dans le donjon
 * \return Code erreur
*/
t_erreur donjon_creer(t_donjon ** donjon, int nb_salle, t_entite * joueur){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_creer() : Double poiteur sur la liste NULL");
        return PTR_NULL;
    }
    if(nb_salle <= 1){
        erreur_save(VALUE_ERROR, "donjon_creer() : Nombre de salle inferieur ou égal à 1");
        return VALUE_ERROR;
    }

    /* Création Donjon */
    *donjon = malloc(sizeof(t_donjon));

    (*donjon)->donjon = malloc(sizeof(t_liste));
    init_liste((*donjon)->donjon);

    /* On sauvegarde les coordonnées du joueur avant d'entrer dans le donjon */
    (*donjon)->x_map_joueur = joueur->hitbox.x;
    (*donjon)->y_map_joueur = joueur->hitbox.y;

    /* Calcul taille donjon */
    int taille_donjon = nb_salle;

    /* Création Structure donjon */
    while(nb_salle--){
        donjon_ajout_salle((*donjon)->donjon, taille_donjon, joueur);
    }

    /* Placement de la salle du boss */
    placer_salle_boss((*donjon)->donjon);

    /* Création structure salle */
    t_salle_donjon * salle = NULL;
    for(en_tete((*donjon)->donjon); !hors_liste((*donjon)->donjon); suivant((*donjon)->donjon)){
        valeur_elt((*donjon)->donjon, (void **)&salle);
        donjon_creer_structure_salle(salle);
    }

    /* Placement du joueur au début du donjon */
    salle = NULL;
    donjon_coord_depart((*donjon)->donjon, &salle);
    joueur->hitbox.x = (salle->x * SIZE + (SIZE / 2)) * width_block_sdl;
    joueur->hitbox.y = (salle->y * MAX_SCREEN + (MAX_SCREEN - 2)) * height_block_sdl;

    
    return OK;
}

/**
 * \fn
 * \param
*/
static t_erreur donjon_ajout_salle(t_liste * donjon, int taille_donjon, t_entite * joueur){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_ajout_salle() : Poiteur sur la liste NULL");
        return PTR_NULL;
    }

    /* Création salle */
    t_salle_donjon * salle = NULL;

    if(liste_vide(donjon)){
        donjon_creer_salle(&salle, taille_donjon / 2, taille_donjon / 2, DONJON_DEPART);
        ajout_droit(donjon, salle);
        return OK;
    }

    /* On sélectionne une salle */
    int i = chercher_salle(donjon, joueur);
    t_salle_donjon * tamp;
    valeur_liste(donjon, i, (void **)&tamp);

    /* On sélectionne une case voisine */
    int choix;
    selection_voisin(tamp, &choix);

    int x = tamp->x;
    int y = tamp->y;
    if(choix == 0){
        x--;
    }else if(choix == 1){
        y--;
    }else if(choix == 2){
        x++;
    }else if(choix == 3){
        y++;
    }
    
    /* On crée la salle puis on l'ajoute à la liste */
    donjon_creer_salle(&salle, x, y, DONJON_INTERMEDIAIRE);
    en_queue(donjon);
    ajout_droit(donjon, salle);
    update_voisin(donjon, taille_donjon);

    return OK;
}

/**
 * \fn
 * \param
*/
static t_erreur donjon_creer_salle(t_salle_donjon ** salle, int x, int y, t_type_salle_donjon type){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_salle() : Doule pointeur sur la salle NULL");
        return PTR_NULL;
    }

    /* Création salle */
    *salle = malloc(sizeof(t_salle_donjon));
    (*salle)->x = x;
    (*salle)->y = y;
    int i;
    for(i = 0; i < 4; i++){
        (*salle)->voisin[i] = 0;
    }

    (*salle)->type = type;

    /* On sélectionne une difficulté */
    if(type == DONJON_DEPART){
        (*salle)->difficulte = AUCUNE;
    }else if(type == DONJON_FIN){
        (*salle)->difficulte = FINAL;
    }else{
        
        int alea = noise2(x, y) % 3;
        
        if(alea == 0)
            (*salle)->difficulte = FACILE;
        else if(alea == 1)
            (*salle)->difficulte = MOYEN;
        else
            (*salle)->difficulte = DIFFICILE;
    }

    return OK;
}

/**
 * \fn
 * \param
*/
static int nb_voisin_salle(t_salle_donjon * salle){
    int nb = 0;
    if(salle == NULL)
        return nb;
    int i;
    for(i = 0; i < 4; i++)
        if(salle->voisin[i] == 0)
            nb++;
    
    return nb;
}

/**
 * \fn
 * \param
*/
static t_erreur selection_voisin(t_salle_donjon * salle, int * choix){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur salle NULL");
        return PTR_NULL;
    }
    if(choix == NULL){
        erreur_save(PTR_NULL, "selection_voisin() : Pointeur sur choix NULL");
        return PTR_NULL;
    }

    /* On sélectionne une salle inexistante */
    t_liste * liste = malloc(sizeof(t_liste));
    init_liste(liste);
    int i;
    for(i = 0; i < 4; i++){
        if(salle->voisin[i] == 0){
            int * tamp = malloc(sizeof(int));
            *tamp = i;
            ajout_droit(liste, (void *)tamp);
        }
    }

    int choix_voisin;
    choix_voisin = noise2(salle->x, salle->y) % taille_liste(liste);
    int *choix_inter;
    valeur_liste(liste, choix_voisin, (void **)&choix_inter);
    *choix = *choix_inter;

    /* On libère la mémoire */
    detruire_liste(liste, free);
    free(liste);
    
    return OK;
}

/**
 * \fn
 * \brief Cherche une salle ayant au moins 1 voisin
 * \param
 * \return La position dans la liste, -1 sinon
*/
static int chercher_salle(t_liste *donjon, t_entite * joueur){
    /* On sélectionne une salle aléatoire */
    int taille_l = taille_liste(donjon);
    
    int i = noise2(joueur->hitbox.x, joueur->hitbox.y) % taille_l;
    
    /* On cherche une salle ayant au moins 1 voisin */
    t_salle_donjon * salle;
    int verif = 0;
    while(!verif){
        valeur_liste(donjon, i, (void **)&salle);

        if(nb_voisin_salle(salle) <= 0){
            if(i >= taille_l - 1)
                i = 0;
            else
                i++;            
        }else{
            verif = 1;
        }
    }
    return i;
}

/**
 * 
*/
static t_erreur update_voisin(t_liste * donjon, int taille_donjon){
    t_salle_donjon *salle_courante, *salle_suivante;

    int i;
    for(i = 0; i < taille_liste(donjon); i++){
        valeur_liste(donjon, i, (void **)&salle_courante);

        for(en_tete(donjon); !hors_liste(donjon); suivant(donjon)){
            valeur_elt(donjon, (void **)&salle_suivante);
            if(salle_courante != salle_suivante){
                if(salle_courante->y == salle_suivante->y){
                    if(salle_courante->x - 1 == salle_suivante->x){
                        salle_courante->voisin[0] = 1;
                        salle_suivante->voisin[2] = 1;
                    }else if(salle_courante->x + 1 == salle_suivante->x){
                        salle_courante->voisin[2] = 1;
                        salle_suivante->voisin[0] = 1;
                    }
                }else if(salle_courante->x == salle_suivante->x){
                    if(salle_courante->y - 1 == salle_suivante->y){
                        salle_courante->voisin[1] = 1;
                        salle_suivante->voisin[3] = 1;
                    }else if(salle_courante->y + 1 == salle_suivante->y){
                        salle_courante->voisin[3] = 1;
                        salle_suivante->voisin[1] = 1;
                    }
                }
            }
            if(salle_courante->x == 0){
                salle_courante->voisin[0] = 1;
            }else if(salle_courante->x == taille_donjon - 1){
                salle_courante->voisin[2] = 1;
            }else if(salle_courante->y == 0){
                salle_courante->voisin[1] = 1;
            }else if(salle_courante->y == taille_donjon - 1){
                salle_courante->voisin[3] = 1;
            }
        }
    }

    return OK;
}

/**
 * 
*/
static t_erreur donjon_creer_structure_salle(t_salle_donjon * salle){
    /* Vérification */
    if(salle == NULL){
        erreur_save(PTR_NULL, "donjon_creer_structure_salle() : Pointeur sur salle NULL");
        return PTR_NULL;
    }

    /* Initialisation structure salle */
    t_liste * liste = malloc(sizeof(t_liste));
    init_liste(liste);
    salle->structure = liste;

    /* Création structure salle */
    t_block * tab = NULL;
    int i;
    for(i = 0; i < SIZE; i++){
        tab = malloc(sizeof(t_block) * MAX_SCREEN);
        int hauteur;

        /* Génération relief plafond */
        hauteur = perlin2d(i, salle->x * salle->y, FREQ * 20, DEPTH) * (MAX_SCREEN / 2);
        if(hauteur >= MAX_SCREEN - 1)
            hauteur = MAX_SCREEN - 1;
        
        int j;
        for(j = 0; j < MAX_SCREEN; j++){
            tab[j].x = i;
            tab[j].y = j;
    
            if(j <= hauteur && i == SIZE / 2 && salle->voisin[1] == 1){
                tab[j].id = AIR;
            }else if(j == MAX_SCREEN - 1 && i == SIZE / 2 && salle->voisin[3] == 1){
                tab[j].id = AIR;
            }else if(j <= hauteur || j == MAX_SCREEN - 1){
                tab[j].id = ROCHE;
            }else{
                tab[j].id = AIR;
            }
        }
        en_queue(liste);
        ajout_droit(liste, tab);
    }

    return OK;
}

/**
 * 
*/
static t_erreur donjon_coord_depart(t_liste * donjon, t_salle_donjon ** salle_dep){
    /* Vérification */
    if(donjon == NULL){
        return PTR_NULL;
    }
    if(salle_dep == NULL){
        return PTR_NULL;
    }

    /* On cherche le départ */
    t_salle_donjon * salle = NULL;
    for(en_tete(donjon); !hors_liste(donjon) && (salle == NULL || salle->type != DONJON_DEPART); suivant(donjon)){
        valeur_elt(donjon, (void**)&salle);
    }

    /* On met à jour les coordonnées */
    *salle_dep = salle;
    
    return OK;
}

/**
 * 
*/
static t_erreur placer_salle_boss(t_liste * donjon){
    /* Vérification */
    if(donjon == NULL){
        return PTR_NULL;
    }

    /* On sélectionne la salle la plus loin de la salle de départ */
    t_salle_donjon * salle_dep = NULL;
    donjon_coord_depart(donjon, &salle_dep);

    t_salle_donjon * salle_max = salle_dep;
    t_salle_donjon * salle = NULL;
    for(en_tete(donjon); !hors_liste(donjon); suivant(donjon)){
        valeur_elt(donjon, (void**)&salle);
        int norme = (salle->x - salle_dep->x) * (salle->y - salle_dep->y);
        int norme2 = (salle_max->x - salle_dep->x) * (salle_max->y - salle_dep->y);
        //fprintf(stderr, "salle: x=%d, y=%d | max: x=%d, y=%d | dep: x=%d, y=%d\n", salle->x, salle->y, salle_max->x, salle_max->y, salle_dep->x, salle_dep->y);
        if(norme > norme2){
            salle_max = salle;
        }
    }

    salle_max->type = DONJON_FIN;
    salle_max->difficulte = FINAL;

    return OK;
}

/**
 * \brief Retourne dans tab la partie du donjon à afficher
*/
static t_erreur tab_fenetre(t_liste * donjon, SDL_Rect pos_perso, t_liste ** tab_fenetre){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "tab_fenetre() : Pointeur sur donjon NULL");
        return PTR_NULL;
    }
    if(tab_fenetre == NULL){
        erreur_save(PTR_NULL, "tab_fenetre() : Double pointeur sur tab NULL");
        return PTR_NULL;
    }
    
    /* Initialisation tableau */
    t_block tab[MAX_SCREEN][SIZE];
    int i, j;
    for(i = 0; i < MAX_SCREEN; i++){
        for(j = 0; j < SIZE; j++){
            tab[i][j].id = AIR;
            tab[i][j].x = j;
            tab[i][j].y = i;
        }
    }
    
    /* Calcule coord extreme fenetre/donjon */
    int x_salle_min = (pos_perso.x / width_block_sdl) - (SIZE / 2);
    int x_donjon_min = x_salle_min / SIZE;
    int x_salle_max = (pos_perso.x / width_block_sdl) + (SIZE / 2);
    int x_donjon_max = x_salle_max / SIZE;
    int y_salle_min = (pos_perso.y / height_block_sdl) - (MAX_SCREEN / 2);
    int y_donjon_min = y_salle_min / MAX_SCREEN;
    int y_salle_max = (pos_perso.y / height_block_sdl) + (MAX_SCREEN / 2);
    int y_donjon_max = y_salle_max / MAX_SCREEN;
    
    /* On ajoute les blocks à la map */
    t_salle_donjon * salle = NULL;
    t_block *colonne = NULL;
    for(en_tete(donjon); !hors_liste(donjon); suivant(donjon)){ //On parcours le donjon
        valeur_elt(donjon, (void **)&salle);

        if(salle->x >= x_donjon_min && salle->x <= x_donjon_max){ 
            if(salle->y >= y_donjon_min && salle->y <= y_donjon_max){
                for(en_tete(salle->structure); !hors_liste(salle->structure); suivant(salle->structure)){  //On parcours la salle
                    valeur_elt(salle->structure, (void **)&colonne);
                    
                    for(i = 0; i < MAX_SCREEN; i++){ //On parcours la colonne de la salle
                        int x_donjon = salle->x * SIZE + colonne[i].x;
                        int y_donjon = salle->y * MAX_SCREEN + colonne[i].y;
                        
                        if(x_donjon >= x_salle_min && x_donjon < x_salle_max){
                            if(y_donjon >= y_salle_min && y_donjon < y_salle_max){
                                tab[y_donjon - y_salle_min][x_donjon - x_salle_min].id = colonne[i].id;
                                tab[y_donjon - y_salle_min][x_donjon - x_salle_min].x = x_donjon;
                                tab[y_donjon - y_salle_min][x_donjon - x_salle_min].y = y_donjon;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Création liste de colonne */
    *tab_fenetre = malloc(sizeof(t_liste));
    init_liste(*tab_fenetre);

    for(j = 0; j < SIZE; j++){
        t_block * colonne = malloc(sizeof(t_block) * MAX_SCREEN);
        for(i = 0; i < MAX_SCREEN; i++){
            colonne[MAX_SCREEN - 1 - i] = tab[i][j];
        }
        en_queue(*tab_fenetre);
        ajout_droit(*tab_fenetre, (void*)colonne);
    }
    
    return OK;
}

/**
 * 
*/
t_erreur donjon_afficher_Term(t_donjon * donjon, t_entite * joueur){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_afficher_Term() : Pointeur sur donjon NULL");
        return PTR_NULL;
    }

    /**/
    t_liste * fenetre = NULL;

    tab_fenetre(donjon->donjon, joueur->hitbox, &fenetre);

    AFF_map_term(fenetre, 0, SIZE-1);

    detruire_liste(fenetre, free);

    return OK;
}

/**
 * 
*/
t_erreur donjon_afficher_SDL(SDL_Renderer * renderer, t_donjon * donjon, t_entite * joueur){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_afficher_SDL() : Pointeur sur donjon NULL");
        return PTR_NULL;
    }
    if(renderer == NULL){
        erreur_save(PTR_NULL, "donjon_afficher_SDL() : Pointeur sur renderer NULL");
        return PTR_NULL;
    }

    /* Initialisation tableau fenetre */
    t_liste * fenetre = NULL;

    tab_fenetre(donjon->donjon, joueur->hitbox, &fenetre);

    AFF_map_sdl(fenetre, renderer, -1);

    detruire_liste(fenetre, free);

    return OK;
}

/**
 * 
*/
t_erreur donjon_gestion(t_donjon * donjon, t_entite * joueur){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_gestion() : Pointeur sur donjon NULL");
        return PTR_NULL;
    }
    if(joueur == NULL){
        erreur_save(PTR_NULL, "donjon_gestion() : Pointeur sur joueur NULL");
        return PTR_NULL;
    }

    /* Initialisation */
    int x_donjon_j = (joueur->hitbox.x / width_block_sdl) / SIZE;
    int y_donjon_j = (joueur->hitbox.y / height_block_sdl) / MAX_SCREEN;
    t_salle_donjon * salle = NULL;

    /* On cherche la salle dans laquelle le joueur est */
    for(en_tete(donjon->donjon); !hors_liste(donjon->donjon) && (salle == NULL || salle->x != x_donjon_j || salle->y != y_donjon_j); suivant(donjon->donjon)){
        valeur_elt(donjon->donjon, &salle);
    }

    /* Gestion mob */


    return OK;
}

/**
 * 
*/
t_erreur donjon_detruire(t_donjon **donjon){
    /* Vérification */
    if(donjon == NULL){
        erreur_save(PTR_NULL, "donjon_detruire() : Double pointeur sur liste NULL");
        return PTR_NULL;
    }
    if(*donjon == NULL){
        return OK;
    }

    /* Destruction donjon */
    detruire_liste((*donjon)->donjon, (void *)donjon_detruire_salle);
    free(*donjon);
    *donjon = NULL;

    return OK;
}

/**
 * 
*/
static void donjon_detruire_salle(t_salle_donjon *salle){
    if(salle != NULL){
        if(salle->structure != NULL){
            detruire_liste(salle->structure, free);
            salle->structure = NULL;
        }
        free(salle);
    }
}
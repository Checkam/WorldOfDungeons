#ifndef __CHEMIN_H__
#define __CHEMIN_H__
/**
 * \file chemin.h
 * \brief Module des primitives servant à la récupération du chemin absolu.
 * \author GALBRUN Tibane
 * \date 09/03/2019
 * \version 0.2
*/
#include <liste.h>
#include <erreur.h>

#define PROJECT_NAME "WorldOfDungeons"

/**
 * \var WOD_PWD
 * \brief Variable Globale contenant le chemin absolu de la racine du projet.
*/
char * WOD_PWD;

/* Décomposition du PWD */
t_erreur decomposer_PWD (t_liste * p, char * pwd);

/* Création du WOD_PWD
Utilisation : getpwd(argv[0],getenv("PWD"));
Ne pas oublier de récupérer les arguments du main :
int main (int argc, char ** argv, char ** env) */
t_erreur getpwd(char * argv, char * env);
t_erreur fusion_PWD(t_liste * env, t_liste * argv);

/* Création chemin à partir de WOD_PWD
Utilisation : creation_chemin ("chemin_après_WOD_PWD",&str_res); */
t_erreur creation_chemin (char * ajout, char ** res);

/* Met en minuscule une chaine de caractère.
str : chaine source
res : chaine resultat */
t_erreur tolower_str (char * str, char ** res);

#endif
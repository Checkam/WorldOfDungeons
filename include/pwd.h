#ifndef __PWD_H__
#define __PWD_H__
/**
 * \file pwd.h
 * \brief Module des primitives servant à la récupération du chemin absolu.
 * \author GALBRUN Tibane
 * \date 07/03/2019
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

/* Création du WOD_PWD */
t_erreur getpwd(char * argv, char * env);
t_erreur fusion_PWD(t_liste * env, t_liste * argv);

/* Création chemin à partir de WOD_PWD */
t_erreur creation_chemin (char * ajout, char ** res);

#endif
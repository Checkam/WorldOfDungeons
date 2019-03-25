#ifndef __BINAIRE_H__
#define __BINAIRE_H__

/**
 * \file binaire.h
 * \brief Module contenant les primitives de gestion de fichier binaire.
 * \author GALBRUN Tibane
 * \date 11 Mars 2019
 * \version 0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>

typedef FILE * t_binaire;

/* Création, Ouverture et Fermeture de fichier Binaire */

/* Ouvre un fichier binaire et le crée s'il n'existe pas. */
t_binaire open_bin (char * dossier, char * name, char * mode);
/* Supprime un fichier binaire. */
t_erreur del_bin (char * dossier, char * name);
/* Ferme un fichier binaire. */
t_erreur close_bin (t_binaire bin);

#endif
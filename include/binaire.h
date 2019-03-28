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

/**
 * \def t_binaire
 * \brief Pointeur sur un fichier de type binaire.
*/
typedef FILE * t_binaire;

/* Création, Ouverture et Fermeture de fichier Binaire */

/* Ouvre un fichier binaire et le crée s'il n'existe pas.
Pour les modes d'ouvertures, ce sont les mêmes que pour le
fopen mais il faut ajouté un 'b'. Ex : wb, wb+, rb, rb+ */
t_binaire Open_BIN (char * dossier, char * name, char * mode);
/* Supprime un fichier binaire. */
t_erreur Del_BIN (char * dossier, char * name);
/* Ferme un fichier binaire. */
t_erreur Close_BIN (t_binaire bin);


/* Ecriture et Lecture dans un fichier Binaire */

/* Ecrit dans un fichier binaire */
t_erreur Write_BIN (void * src, int taille_elem, int nb_elem, t_binaire bin);
/* Lit dans un fichier binaire. Il faut être en début de
fichier pour lire. Utiliser fstart si pas au début. */
t_erreur Read_BIN (void * dest, int taille_elem, int nb_elem, t_binaire bin);

/* Remet au début du fichier */
t_erreur FStart_BIN (t_binaire file);

#endif
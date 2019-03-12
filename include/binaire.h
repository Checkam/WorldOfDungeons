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

FILE * open_bin (char * dossier, char * name, char * mode);
t_erreur del_bin (char * dossier, char * name);

#endif
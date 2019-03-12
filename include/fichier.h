#ifndef __FICHIER_H__
#define __FICHIER_H__

/**
 * \file fichier.h
 * \brief Module contenant les primitives de gestion de fichier.
 * \author GALBRUN Tibane
 * \date 12 Mars 2019
 * \version 0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>

FILE * open_file (char * dossier, char * name, char * ext, char * mode);
t_erreur del_file (char * dossier, char * name, char * ext);

char * concat_str (char * str1, char * str2);

#endif
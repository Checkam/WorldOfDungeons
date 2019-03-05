/**
 * \file json.h
 * \brief Module contenant les primitives et les structures permettant l'écriture et la lecture de fichier JSON.
 * \author GALBRUN Tibane
 * \version 0.1
 * \date 4 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>

/* Primitives de création, de fermeture et de suppression */
FILE * new_json (char * name);
int del_json (char * name);

/* Primitives d'écriture */
int write_json (FILE * file, char * key, void * value, char value_type);
int open_json_obj (FILE * file);
int close_json_obj (FILE * file);

/* Primitives de lecture */

/* Primitives Autres */
char * concat_str (char * str1, char * str2);
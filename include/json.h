/**
 * \file json.h
 * \brief Module contenant les primitives et les structures permettant l'écriture et la lecture de fichier JSON.
 * \author GALBRUN Tibane
 * \version 0.3
 * \date 5 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>

/* Defines */
#define LINE_MAX_WIDTH 200 /* Taille maximum d'un objet JSON */

/* Primitives de création, d'ouverture, de fermeture et de suppression */
FILE * new_json (char * name);
int del_json (char * name);
FILE * open_json (char * name);

/* Primitives d'écriture */
int write_json (FILE * file, char * key, void * value, char value_type);
int open_json_obj (FILE * file);
int close_json_obj (FILE * file);

/* Primitives de lecture */
int extract_json_obj (FILE * file, char * obj);
int read_json_obj (char * obj, char * key, void * value, char value_type);

/* Primitives Autres */
char * concat_str (char * str1, char * str2);
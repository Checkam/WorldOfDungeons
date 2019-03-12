#ifndef __JSON_H__
#define __JSON_H__
/**
 * \file json.h
 * \brief Module contenant les primitives et les structures permettant l'écriture et la lecture de fichier JSON.
 * \author GALBRUN Tibane
 * \version 0.3
 * \date 5 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>

/* Primitives de création, d'ouverture, de fermeture et de suppression */

/* Création et/ou Ouverture d'un fichier JSON /
Utilisation : FILE * file = open_json("dossier/JSON", "name", "mode") */
FILE * open_json (char * dossier, char * name, char * mode);
/* Suppression d'un fichier JSON /
Utilisation : del_json("dossier/JSON", "name") */
t_erreur del_json (char * dossier, char * name);

/* Primitives d'écriture */

/* Ecriture dans un fichier JSON d'une valeur avec sa clé /
Utilisation : write_json(file, cle, valeur, type_de_la_valeur) */
t_erreur write_json (FILE * file, char * key, void * value, char * value_type);
/* Ouverture d'un nouvel objet dans un fichier JSON /
Utilisation : open_json_obj(file) */
t_erreur open_json_obj (FILE * file);
/* Fermeture d'un objet dans un fichier JSON /
Utilisation : close_json_obj(file) */
t_erreur close_json_obj (FILE * file);

/* Primitives de lecture */

/* Extraction d'un objet dans un fichier JSON /
Utilisation : extract_json_obj(file, &obj) */
t_erreur extract_json_obj (FILE * file, char ** obj);
/* Lit le contenu d'un objet /
Utilisation : read_json_obj(obj,cle,valeur,type_de_la_valeur)
type_de_la_valeur = [d,s,f] */
t_erreur read_json_obj (char * obj, char * key, void * value, char * value_type);

/* Remet au début du fichier */
t_erreur fstart (FILE * file);

#endif
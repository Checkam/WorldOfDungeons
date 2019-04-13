#ifndef __JSON_H__
#define __JSON_H__
/**
 * \file json.h
 * \brief Module contenant les primitives et les structures permettant l'écriture et la lecture de fichier JSON.
 * \author GALBRUN Tibane
 * \version 0.4
 * \date 5 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>
#include <inttypes.h>
#include <liste.h>

typedef FILE* t_json;
t_liste json_objects; // Liste contenant tous les objets JSON.

/* Primitives de création, d'ouverture, de fermeture et de suppression */

/* Création et/ou Ouverture d'un fichier JSON /
Utilisation : JSON_Open("dossier/JSON", "name", "mode") */
t_erreur JSON_Open (char * dossier, char * name, char * mode);
/* Suppression d'un fichier JSON /
Utilisation : JSON_Delete("dossier/JSON", "name") */
t_erreur JSON_Delete (char * dossier, char * name);
/* Ferme un fichier JSON */
t_erreur JSON_Close ();

/* Primitives d'écriture */

/* Ecriture dans un fichier JSON d'une valeur avec sa clé /
Utilisation : JSON_Write(cle, valeur, type_de_la_valeur)
type_de_la_valeur = [d,[d8...d64],s,f,u,[u8...u64]] */
t_erreur JSON_Write (char * key, void * value, char * value_type);
/* Ouverture d'un nouvel objet dans un fichier JSON /
Utilisation : JSON_Open_Object() */
t_erreur JSON_Open_Object ();
/* Fermeture d'un objet dans un fichier JSON /
Utilisation : JSON_Close_Object() */
t_erreur JSON_Close_Object ();

/* Primitives de lecture */

/* Extraction d'un objet dans un fichier JSON /
Utilisation : JSON_Extract_Object(file, &obj) */
t_erreur JSON_Extract_Object (t_json file, char ** obj);
/* Lit le contenu d'un objet /
Utilisation : JSON_Read_Object(obj,cle,valeur,type_de_la_valeur)
type_de_la_valeur = [d,[d8...d64],s,f,u,[u8...u64]] */
t_erreur JSON_Read_Object (char * obj, char * key, void * value, char * value_type);

/* Remet au début du fichier */
t_erreur fstart (t_json file);

#endif
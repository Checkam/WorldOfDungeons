/**
 * \file json.c
 * \brief Module qui lit et écrit des fichiers au format JSON.
 * \author GALBRUN Tibane
 * \version 0.1
 * \date 4 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>

/**
 * \fn FILE * new_json (char * name)
 * \brief Créer, s'il ne l'est pas, le fichier JSON et l'ouvre en écriture.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json'.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * new_json (char * name)
{
    char * name_json = concat_str (name,".json");
    FILE * file = fopen(name_json,"w");
    free(name_json);
    return file;
}

/**
 * \fn int del_json (char * name)
 * \brief Supprime un fichier JSON.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json' à supprimer.
 * \return Un entier valant 0 si tout c'est bien passé.
*/
int del_json (char * name)
{
    char * name_json = concat_str (name,".json");
    FILE * file = fopen(name_json,"r");
    fclose (file);
    free(name_json);
    if (file != NULL)
    {
        remove (name_json);
        return 0;
    }
    return 1;
}

/**
 * \fn char * concat_str (char * str1, char * str2)
 * \brief Concatène 2 chaine de caractère.
 * \param str1 Chaine de caractère de gauche.
 * \param str2 Chaine de caractère de droite.
 * \return Une chaine de caractère résultat de la concatènation.
*/
char * concat_str (char * str1, char * str2)
{
    char * str_res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    strcpy (str_res, str1);
    strcat (str_res, str2);
    return str_res;
}

/**
 * \fn int write_json (FILE * file, char * key, void * value, int (*write) (FILE *, void *))
 * \brief Ecrit un objet au format JSON dans un fichier.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu le couple clé/valeur '{key:value}'.
 * \param file Le fichier ou écrire.
 * \param key La clé correspondant à la valeur.
 * \param value La valeur à écrire.
 * \param (*write) La fonction pour écrire.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int write_json (FILE * file, char * key, void * value, int (*write) (FILE *, void *))
{
    fprintf(file,"{%s:",key);
    write(file,value);
    fprintf(file,"}\n");
    return 0;
}

/**
 * \fn int write_int (FILE * file, int * value)
 * \brief Ecrit un entier dans un fichier.
 * \param file Le fichier ou écrire.
 * \param La valeur à écrire.
 * \return Un entier pour savoir si tout c'est bien passée.
*/
int write_int (FILE * file, int * value)
{
    fprintf(file,"%d",*value);
    return 0;
}

/**
 * \fn int write_str (FILE * file, char * value)
 * \brief Ecrit une chaine de caractère dans un fichier.
 * \param file Le fichier ou écrire.
 * \param La valeur à écrire.
 * \return Un entier pour savoir si tout c'est bien passée.
*/
int write_str (FILE * file, char * value)
{
    fprintf(file,"%s",value);
    return 0;
}

/**
 * \fn int write_float (FILE * file, float * value)
 * \brief Ecrit un float dans un fichier.
 * \param file Le fichier ou écrire.
 * \param La valeur à écrire.
 * \return Un entier pour savoir si tout c'est bien passée.
*/
int write_float (FILE * file, float * value)
{
    fprintf(file,"%.2f",*value);
    return 0;
}
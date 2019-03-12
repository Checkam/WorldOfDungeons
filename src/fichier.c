/**
 * \file fichier.c
 * \brief Module qui gère l'ouverture et la supression de fichier.
 * \author GALBRUN Tibane
 * \version 0.1
 * \date 12 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <binaire.h>
#include <chemin.h>
#include <erreur.h>
#include <fichier.h>

/**
 * \fn FILE * open_file (char * dossier, char * name, char * ext, char * mode)
 * \brief Créer, s'il ne l'est pas, le fichier et l'ouvre.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier.
 * \param name Chaine de caractère représenant le nom du fichier.
 * \param ext Extension du fichier.
 * \param mode Mode d'ouverture du fichier.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * open_file (char * dossier, char * name, char * ext, char * mode)
{
    /* Création chemin + nom_fichier */
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_ext = concat_str (name,ext);

    /* Création et Ouverture Fichier */
    char * lieu = concat_str (chemin,name_ext);
    FILE * file = fopen(lieu,mode);

    free(chemin);
    free(lieu);
    free(name_ext);
    return file;
}

/**
 * \fn int del_file (char * dossier, char * name, char * ext)
 * \brief Supprime un fichier.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier.
 * \param name Chaine de caractère représenant le nom du fichier à supprimer.
 * \param ext Extension du fichier.
 * \return Une erreur s'il y en a une.
*/
t_erreur del_file (char * dossier, char * name, char * ext)
{
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_ext = concat_str (name,ext);
    char * lieu = concat_str (chemin,name_ext);

    FILE * file = fopen(lieu,"r");
    fclose(file);
    if (file)
    {
        remove(lieu);
        free(lieu);
        free(chemin);
        free(name_ext);
        return OK;
    }
    free(chemin);
    free(lieu);
    free(name_ext);
    return REMOVE_FILE_ERROR;
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
    strcpy(str_res, str1);
    strcat(str_res, str2);
    return str_res;
}
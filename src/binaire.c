/**
 * \file binaire.c
 * \brief Module qui lit et écrit des fichiers binaires.
 * \author GALBRUN Tibane
 * \version 0.1
 * \date 11 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <binaire.h>
#include <chemin.h>
#include <erreur.h>

/**
 * \fn FILE * open_bin (char * dossier, char * name, char * mode)
 * \brief Créer, s'il ne l'est pas, le fichier Binaire et l'ouvre.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier binaire.
 * \param name Chaine de caractère représenant le nom du fichier.
 * \param mode Mode d'ouverture du fichier.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * open_bin (char * dossier, char * name, char * mode)
{
    /* Création chemin + nom_fichier */
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_dat = concat_string (name,".dat");

    /* Création et Ouverture Fichier */
    char * lieu = concat_string (chemin,name_dat);
    FILE * file = fopen(lieu,mode);

    free(chemin);
    free(lieu);
    free(name_dat);
    return file;
}

/**
 * \fn int del_bin (char * dossier, char * name)
 * \brief Supprime un fichier Binaire.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier binaire.
 * \param name Chaine de caractère représenant le nom du fichier à supprimer.
 * \return Une erreur s'il y en a une.
*/
t_erreur del_bin (char * dossier, char * name)
{
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_dat = concat_string (name,".dat");
    char * lieu = concat_string (chemin,name_dat);

    FILE * file = fopen(lieu,"r");
    fclose(file);
    if (file)
    {
        remove(lieu);
        free(lieu);
        free(chemin);
        free(name_dat);
        return OK;
    }
    free(chemin);
    free(lieu);
    free(name_dat);
    return REMOVE_FILE_ERROR;
}

/**
 * \fn char * concat_string (char * str1, char * str2)
 * \brief Concatène 2 chaine de caractère.
 * \param str1 Chaine de caractère de gauche.
 * \param str2 Chaine de caractère de droite.
 * \return Une chaine de caractère résultat de la concatènation.
*/
char * concat_string (char * str1, char * str2)
{
    char * str_res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    strcpy(str_res, str1);
    strcat(str_res, str2);
    return str_res;
}
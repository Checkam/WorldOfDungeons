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
#include <fichier.h>

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
    return open_file(dossier,name,".dat",mode);
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
    return del_file(dossier,name,".dat");
}
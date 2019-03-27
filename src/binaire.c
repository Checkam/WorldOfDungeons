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

/* *******************************************************
 * 
 *   Création, Ouverture et Fermeture de fichier Binaire
 *
 * ******************************************************* */

/**
 * \fn t_binaire Open_BIN (char * dossier, char * name, char * mode)
 * \brief Créer, s'il ne l'est pas, le fichier Binaire et l'ouvre.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier binaire.
 * \param name Chaine de caractère représenant le nom du fichier.
 * \param mode Mode d'ouverture du fichier.
 * \return Un pointeur sur le fichier ouvert.
*/
t_binaire Open_BIN (char * dossier, char * name, char * mode)
{
    return open_file(dossier,name,".dat",mode);
}

/**
 * \fn int Del_BIN (char * dossier, char * name)
 * \brief Supprime un fichier Binaire.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le fichier binaire.
 * \param name Chaine de caractère représenant le nom du fichier à supprimer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Del_BIN (char * dossier, char * name)
{
    return del_file(dossier,name,".dat");
}

/**
 * \fn t_erreur close_bin (t_binaire bin)
 * \brief Ferme un fichier Binaire.
 * \param bin Le fichier à fermer.
 * \return Une erreur s'il y en a une.
*/
t_erreur Close_BIN (t_binaire bin)
{
    if (!bin) return PTR_NULL;
    fclose(bin);
    return OK;
}

/* *******************************************************
 * 
 *      Ecriture et Lecture dans un fichier Binaire
 *
 * ******************************************************* */

/**
 * \fn t_erreur Write_BIN (void * src, int taille_elem, int nb_elem, t_binaire bin)
 * \brief Ecrit dans un fichier Binaire.
 * \param src L'adresse du 1er élèment à écrire.
 * \param taille_elem La taille d'un élèment.
 * \param nb_elem Le nombre d'élèment à écrire.
 * \param bin Le fichier où écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur Write_BIN (void * src, int taille_elem, int nb_elem, t_binaire bin)
{
    if (!src) return PTR_NULL;
    if (!bin) return FILE_ERROR;
    if (taille_elem <= 0 || nb_elem <= 0) return VALUE_ERROR;

    int nb_write; // Nb elem écrit dans le fichier
    nb_write = fwrite(src,taille_elem,nb_elem,bin);

    if (nb_write != nb_elem) return FILE_ERROR;

    return OK;
}

/**
 * \fn t_erreur Read_BIN (void * dest, int taille_elem, int nb_elem, t_binaire bin)
 * \brief Lit le contenu d'un fichier Binaire.
 * \param dest L'adresse de l'endroit où sauvegarder ce qu'on récupère.
 * \param taille_elem La taille d'un élèment.
 * \param nb_elem Le nombre d'élèment à lire.
 * \param bin Le fichier où lire.
 * \return Une erreur s'il y en a une.
*/
t_erreur Read_BIN (void * dest, int taille_elem, int nb_elem, t_binaire bin)
{
    if (!dest) return PTR_NULL;
    if (!bin) return FILE_ERROR;
    if (taille_elem <= 0 || nb_elem <= 0) return VALUE_ERROR;

    int nb_lus; // Nb elem lus dans le fichier
    nb_lus = fread(dest,taille_elem,nb_elem,bin);

    if (nb_lus != nb_elem) return FILE_ERROR;

    return OK;
}

/**
 * \fn t_erreur FStart_BIN (t_binaire bin)
 * \brief Remet le pointeur file au début du fichier.
 * \param bin Le fichier où repartir du début.
 * \return Une erreur s'il y en a une.
*/
t_erreur FStart_BIN (t_binaire file)
{
    if (!file) return FILE_ERROR;
    fseek(file, 0, SEEK_SET);
    return OK;
}
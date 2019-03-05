/**
 * \file erreur.c
 * \author Jasmin GALBRUN
 * \version 1
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 */
#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>

/**
 * \struct t_erreur_s
 * \brief Contient l'id du code erreur + le message correspondant à l'erreur
*/
typedef struct s_erreur
{
    t_erreur id;
    char * msg;
} t_erreur_s;

//Tableau contenant toutes erreurs + les messages correspondants
t_erreur_s tab_err = {
    {FILE_ERROR, "Erreur de fichier"},
    {OPEN_FILE_ERROR, "Erreur d ouverture du fichier"},
    {CLOSE_FILE_ERROR, "Erreur de fermeture du fichier"},
    {VALUE_ERROR, "Erreur de valeur"},
    {ERROR_NOT_EXIST, "Cette erreur n existe pas"},
    {OK, "Tout c est bien passer"}  //Toujours laisser OK en dernier
}

/**
 * \fn t_erreur aff_erreur(t_erreur code_erreur)
 * \param code_erreur Code erreur que le programme doit afficher
 * \return Retourne une erreur, OK si tout c'est bien passé
*/
t_erreur aff_erreur(t_erreur code_erreur){
    int i;
    for(i = 0; tab_err[i].id != OK; i++){
        if(tab_err[i].id == code_erreur){
            break;
        }
    }

    if(tab_err[i].id != code_erreur){
        fprintf(stderr, "Erreur : Code erreur %d non trouve\n", code_erreur);
        return ERROR_NOT_EXIST;
    }

    fprintf(stderr, "Erreur : [%d] - %s\n", tab_err[i].id, tab_err[i].msg);
    return OK;
}
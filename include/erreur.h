/**
 * \file erreur.h
 * \author Jasmin GALBRUN
 * \version 1
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 * 
 * \enum t_erreur
 * \brief Contient tout les codes erreurs
 */
typedef enum e_erreur{
    OK,
    FILE_ERROR,
    OPEN_FILE_ERROR,
    CLOSE_FILE_ERROR,
    VALUE_ERROR,
    ERROR_NOT_EXIST
}t_erreur;

t_erreur aff_erreur(t_erreur code_erreur);
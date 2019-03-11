#ifndef __ERREUR_H__
#define __ERREUR_H__
/**
 * \file erreur.h
 * \author Jasmin GALBRUN
 * \version 2
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 */

/**
 * \def NB_ERREUR
 * \brief Contient le nombre d'erreur.
 * \brief A modifier à chaque rajout d'une erreur.
*/
#define NB_ERREUR 13

/**
 * \enum t_erreur
 * \brief Contient tout les codes erreurs
*/
typedef enum e_erreur{
    OK,
    FILE_ERROR,
    OPEN_FILE_ERROR,
    CLOSE_FILE_ERROR,
    VALUE_ERROR,
    ERROR_NOT_EXIST,
    REMOVE_FILE_ERROR,
    PTR_NULL,
    PTR_VALUE_ERROR,
    TYPE_ERROR,
    UNDEFINED_MENU,
    INCORRECT_MENU_TYPE,
    KEY_NOT_FOUND
}t_erreur;

t_erreur aff_erreur(t_erreur code_erreur, char * msg_detail);

#endif
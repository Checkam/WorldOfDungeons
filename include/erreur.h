/**
 * \file erreur.h
 * \author Jasmin GALBRUN
<<<<<<< HEAD
 * \version 2
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 */

/**
 * \def NB_ERREUR
 * \brief Contient le nombre d'erreur.
 * \brief A modifier à chaque rajout d'une erreur.
*/
#define NB_ERREUR 10

/**
 * \enum t_erreur
 * \brief Contient tout les codes erreurs
*/
=======
 * \version 1
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 * 
 * \enum t_erreur
 * \brief Contient tout les codes erreurs
 */
>>>>>>> 9b712c7... ADD erreur.c + erreur.h
typedef enum e_erreur{
    OK,
    FILE_ERROR,
    OPEN_FILE_ERROR,
    CLOSE_FILE_ERROR,
    VALUE_ERROR,
<<<<<<< HEAD
    ERROR_NOT_EXIST,
    REMOVE_FILE_ERROR,
    PTR_VALUE_ERROR,
    TYPE_ERROR,
    KEY_NOT_FOUND
}t_erreur;

t_erreur aff_erreur(t_erreur code_erreur);
=======
    ERROR_NOT_EXIST
}t_erreur;
>>>>>>> 9b712c7... ADD erreur.c + erreur.h

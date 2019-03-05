/**
 * \file erreur.c
 * \author Jasmin GALBRUN
<<<<<<< HEAD
 * \version 2
=======
 * \version 1
>>>>>>> 9b712c7... ADD erreur.c + erreur.h
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 */
#include <stdio.h>
#include <stdlib.h>
#include <erreur.h>

<<<<<<< HEAD
=======
#define NB_ERREUR 5

>>>>>>> 9b712c7... ADD erreur.c + erreur.h
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
<<<<<<< HEAD
t_erreur_s tab_err[NB_ERREUR] = {
=======
t_erreur_s tab_err = {
    {OK, "Tout c est bien passer"},
>>>>>>> 9b712c7... ADD erreur.c + erreur.h
    {FILE_ERROR, "Erreur de fichier"},
    {OPEN_FILE_ERROR, "Erreur d ouverture du fichier"},
    {CLOSE_FILE_ERROR, "Erreur de fermeture du fichier"},
    {VALUE_ERROR, "Erreur de valeur"},
<<<<<<< HEAD
    {ERROR_NOT_EXIST, "Cette erreur n existe pas"},
    {REMOVE_FILE_ERROR, "La Suppression du fichier a echoue"},
    {PTR_VALUE_ERROR, "La valeur de Pointeur est Incorrect"},
    {TYPE_ERROR, "Le Type est Incorrect"},
    {KEY_NOT_FOUND, "La Cle n'a pas ete trouve"},
    {OK, "Tout c est bien passer"}  //Toujours laisser OK en dernier
};
=======
    {ERROR_NOT_EXIST, "Cette erreur n existe pas"}
}
>>>>>>> 9b712c7... ADD erreur.c + erreur.h

/**
 * \fn t_erreur aff_erreur(t_erreur code_erreur)
 * \param code_erreur Code erreur que le programme doit afficher
 * \return Retourne une erreur, OK si tout c'est bien passé
*/
<<<<<<< HEAD
t_erreur aff_erreur(t_erreur code_erreur)
{
    /* On cherche l'erreur */
    int i;
    for(i = 0; tab_err[i].id != OK && tab_err[i].id != code_erreur; i++);

    /* On affiche msg erreur si erreur non trouve */
    if(tab_err[i].id != code_erreur){
        aff_erreur(ERROR_NOT_EXIST);
=======
t_erreur aff_erreur(t_erreur code_erreur){
    int i;
    for(i = 0; i < NB_ERREUR; i++){
        if(tab_err[i].id == code_erreur){
            break;
        }
    }

    if(i >= NB_ERREUR){
        fprintf(stderr, "Erreur : Code erreur %d non trouve\n", code_erreur);
>>>>>>> 9b712c7... ADD erreur.c + erreur.h
        return ERROR_NOT_EXIST;
    }

    fprintf(stderr, "Erreur : [%d] - %s\n", tab_err[i].id, tab_err[i].msg);
    return OK;
}
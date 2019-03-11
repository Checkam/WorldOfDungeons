/**
 * \file erreur.c
 * \author Jasmin GALBRUN
 * \version 2
 * \date 05/03/2019
 * \brief Module de gestion des erreurs
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <erreur.h>
#include <chemin.h>

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
t_erreur_s tab_err[NB_ERREUR] = {
    {FILE_ERROR, "Erreur de fichier"},
    {OPEN_FILE_ERROR, "Erreur d ouverture du fichier"},
    {CLOSE_FILE_ERROR, "Erreur de fermeture du fichier"},
    {VALUE_ERROR, "Erreur de valeur"},
    {ERROR_NOT_EXIST, "Cette erreur n existe pas"},
    {REMOVE_FILE_ERROR, "La Suppression du fichier a echoue"},
    {PTR_NULL, "Le pointeur est NULL"},
    {PTR_VALUE_ERROR, "La valeur de Pointeur est Incorrect"},
    {TYPE_ERROR, "Le Type est Incorrect"},
    {UNDEFINED_MENU, "Le pointeur sur le menu est NULL"},
    {INCORRECT_MENU_TYPE, "Type de menu incorrect"},
    {KEY_NOT_FOUND, "La Cle n'a pas ete trouve"},
    {OK, "Tout c est bien passer"}  //Toujours laisser OK en dernier
};

/**
 * \fn t_erreur aff_erreur(t_erreur code_erreur, char * msg_detail)
 * \param code_erreur Code erreur que le programme doit afficher
 * \return Retourne une erreur, OK si tout c'est bien passé
*/
t_erreur aff_erreur(t_erreur code_erreur, char * msg_detail)
{
    /* On cherche l'erreur */
    int i;
    for(i = 0; tab_err[i].id != OK && tab_err[i].id != code_erreur; i++);
    printf("C\n");
    /* On affiche msg erreur si erreur non trouve */
    if(tab_err[i].id != code_erreur){
        aff_erreur(ERROR_NOT_EXIST, NULL);
        return ERROR_NOT_EXIST;
    }

    /* Création ou ajout du fichier d'enregistrement */
    struct tm * temps = localtime((const time_t*)time(NULL));
    char * nom_fichier = NULL;
    char * fichier_log = NULL;

    sprintf(nom_fichier, "log/%d-%d-%d_erreur_log.txt", temps->tm_mday, temps->tm_mon + 1, temps->tm_year + 1900);
    creation_chemin(nom_fichier, &fichier_log);
    FILE * log_erreur = fopen(fichier_log, "a");
    if(log_erreur == NULL){
        return PTR_NULL;
    }

    if(msg_detail){
        fprintf(log_erreur, "%d:%d:%d - Erreur : [%d] - %s : %s\n", temps->tm_hour, temps->tm_min, temps->tm_sec, code_erreur, tab_err[i].msg, msg_detail);
    }else{
        fprintf(log_erreur, "%d:%d:%d - Erreur : [%d] - %s\n", temps->tm_hour, temps->tm_min, temps->tm_sec, code_erreur, tab_err[i].msg);
    }

    free(fichier_log);
    free(nom_fichier);
    fclose(log_erreur);
    return OK;
}
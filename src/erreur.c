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
#include <sys/stat.h>
#include <sys/types.h>
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
    {FILE_ERROR, "FILE ERROR"},
    {OPEN_FILE_ERROR, "OPEN FILE ERROR"},
    {CLOSE_FILE_ERROR, "CLOSE FILE ERROR"},
    {VALUE_ERROR, "VALUE ERROR"},
    {ERROR_NOT_EXIST, "ERROR NOT EXIST"},
    {REMOVE_FILE_ERROR, "REMOVE FILE ERROR"},
    {PTR_NULL, "POINTEUR NULL"},
    {PTR_VALUE_ERROR, "POINTEUR VALUE ERROR"},
    {TYPE_ERROR, "TYPE ERROR"},
    {UNDEFINED_MENU, "UNDEFINED MENU"},
    {INCORRECT_MENU_TYPE, "INCORRECT MENU TYPE"},
    {KEY_NOT_FOUND, "KEY NOT FOUND"},
    {OK, "OK"}  //Toujours laisser OK en dernier
};

/**
 * \fn t_erreur aff_erreur(t_erreur code_erreur, char * msg_detail)
 * \param code_erreur Code erreur que le programme doit afficher
 * \return Retourne une erreur, OK si tout c'est bien passé
*/
t_erreur erreur_save(t_erreur code_erreur, char * msg_detail)
{
    /* On cherche l'erreur */
    int i;
    for(i = 0; tab_err[i].id != OK && tab_err[i].id != code_erreur; i++);
    
    /* On affiche msg erreur si erreur non trouve */
    if(tab_err[i].id != code_erreur){
        erreur_save(ERROR_NOT_EXIST, NULL);
        return ERROR_NOT_EXIST;
    }

    /* Création ou ajout du fichier d'enregistrement */
    time_t timestamp = time(NULL);
    struct tm * temps = localtime(&timestamp);
    char nom_fichier[300];
    char * fichier_log = NULL;
    char * path_dir = NULL;

    sprintf(nom_fichier, "log/%d:%d:%d-erreur_log.txt", temps->tm_mday, temps->tm_mon + 1, temps->tm_year + 1900);
    if(creation_chemin(nom_fichier, &fichier_log) != OK){
        return PTR_NULL;
    }
    if(creation_chemin("log", &path_dir) != OK){
        return PTR_NULL;
    }
    
    /* Création du dossier log */
    mkdir(path_dir, S_IRWXU | S_IRWXG | S_IROTH);
    
    FILE * log_erreur = fopen(fichier_log, "a");
    if(log_erreur == NULL){
        return PTR_NULL;
    }

    if(msg_detail){
        fprintf(log_erreur, "%d:%d:%d - %s : %s\n", temps->tm_hour, temps->tm_min, temps->tm_sec, tab_err[i].msg, msg_detail);
    }else{
        fprintf(log_erreur, "%d:%d:%d - %s\n", temps->tm_hour, temps->tm_min, temps->tm_sec, tab_err[i].msg);
    }

    free(path_dir);
    free(fichier_log);
    fclose(log_erreur);
    return OK;
}

/**
 * \fn t_erreur erreur_afficher(t_erreur code_erreur, char * msg_detail)
 * \param
*/
t_erreur erreur_afficher(t_erreur code_erreur, char * msg_detail){
    /* On cherche l'erreur */
    int i;
    for(i = 0; tab_err[i].id != OK && tab_err[i].id != code_erreur; i++);
    
    /* On affiche msg erreur si erreur non trouve */
    if(tab_err[i].id != code_erreur){
        erreur_save(ERROR_NOT_EXIST, NULL);
        return ERROR_NOT_EXIST;
    }

    if(msg_detail){
        fprintf(stderr, "%s - %s\n", tab_err[i].msg, msg_detail);
    }else{
        fprintf(stderr, "%s\n", tab_err[i].msg);
    }

    return OK;
}
/**
 * \file chemin.c
 * \brief Module servant à récupérer le chemin absolu de la racine du projet.
 * \author GALBRUN Tibane
 * \date 09/03/2019
 * \version 0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <chemin.h>
#include <liste.h>
#include <erreur.h>
#include <string.h>
#include <ctype.h>

/**
 * \fn t_erreur decomposer_PWD (t_liste * p, char * pwd)
 * \brief Décompose dans une liste le PWD.
 * \param p La liste où mettre ce qui a été décomposé.
 * \param pwd Le PWD à décomposer.
 * \return Une erreur s'il y en a une.
*/
t_erreur decomposer_PWD (t_liste * p, char * pwd)
{
    /* Erreur : pointeur NULL */
    if (!p || !pwd) return PTR_NULL;

    int i, taille, taille_pwd;
    for (i = taille = 0, taille_pwd = strlen(pwd), en_tete(p); i <= taille_pwd; i++)
    {
        if ((pwd[i] == '/' || !pwd[i]) && taille)
        {
            char * tamp = malloc(sizeof(char) * taille + 1);
            int j, deb;
            for (j = i - taille, deb = 0; j < i; j++, deb++)
                tamp[deb] = pwd[j];
            tamp[deb] = '\0';
            ajout_droit(p,tamp);
            taille = 0;
        }else if (pwd[i] != '/')
            taille ++;
    }

    return OK;
}

/**
 * \fn void getpwd(char * argv, char * env)
 * \brief Récupère le chemin absolu de la racine de WOD.
 * \param argv Le PWD utiliser pour connaitre le WOD_PWD.
 * \param env Le PWD utiliser pour connaitre le WOD_PWD.
 * \return Une erreur s'il y en a une.
*/
t_erreur pwd_init(char * argv, char * env)
{
    /* Erreur : pointeur NULL */
    if (!argv || !env) return PTR_NULL;

    /* Liste contenant la décomposition des 2 PWD */
    t_liste env_dec, argv_dec;
    init_liste(&env_dec);
    init_liste(&argv_dec);

    /* Récupération des décompositions */
    decomposer_PWD(&argv_dec, argv);
    decomposer_PWD(&env_dec, env);

    /* Traitement et Création de WOD_PWD */
    fusion_PWD(&env_dec, &argv_dec);

    /* Destruction des Listes */
    detruire_liste(&env_dec, free);
    detruire_liste(&argv_dec, free);

    return OK;
}

/**
 * \fn t_erreur pwd_quit(void)
 * \brief Unset la variable globale WOD_PWD.
 * \return Une erreur s'il y en a une.
*/
t_erreur pwd_quit(void)
{
    free(WOD_PWD);
    return OK;
}

/**
 * \fn t_erreur fusion_PWD(t_liste * env, t_liste * argv)
 * \brief Récupère le chemin absolu de la racine de WOD.
 * \brief Met à jour la valeur de WOD_PWD, qui sera accessible de tout le programme.
 * \param env Le PWD utiliser pour connaitre le WOD_PWD.
 * \param argv Le PWD utiliser pour connaitre le WOD_PWD.
 * \return Une erreur s'il y en a une.
*/
t_erreur fusion_PWD(t_liste * env, t_liste * argv)
{
    /* Erreur : pointeur NULL */
    if (!argv || !env) return PTR_NULL;

    /* Mise en minuscule */
    char * project_name_min;
    char * val_min;
    tolower_str(PROJECT_NAME,&project_name_min);

    /* Construction du WOD_PWD dans la liste env */
    char * val;
    int check = 0;

    /* On regarde si PROJECT_NAME est dans env */
    for (en_tete(env); !hors_liste(env); suivant(env))
    {
        valeur_elt(env,(void **)&val);
        tolower_str(val,&val_min);
        if (!strcmp(project_name_min,val_min)) check = 1;
        else if (check) oter_elt(env,free);
        free(val_min);
    }
    /* Sinon on va voir argv */
    if (!check)
    {
        en_tete(argv); en_queue(env);
        valeur_elt(argv,(void **)&val);
        tolower_str(val,&val_min);
        while (strcmp(project_name_min,val_min) && !hors_liste(argv))
        {
            if (strcmp(".",val))
            {
                /* Si '..', on enleve un elem à env sinon on ajoute un elem à env */
                if(!strcmp("..",val))
                    oter_elt(env,free);
                else{
                    ajout_droit(env,val);
                    oter_elt(argv,NULL);
                }
            }
            free(val_min);
            suivant(argv);
            valeur_elt(argv,(void **)&val);
            tolower_str(val,&val_min);
        }
        ajout_droit(env,val);
        oter_elt(argv,NULL);
        free(val_min);
    }

    /* Fusion des élèments de env pour reconstruction du WOD_PWD */
    char * pwd;

    /* Début du PWD avec "/val/" */
    en_tete(env);
    valeur_elt(env,(void **)&val);
    pwd = malloc(sizeof(char) * strlen(val) + 3);
    strcpy(pwd,"/");
    strcat(pwd,val);
    strcat(pwd,"/");
    suivant(env);

    /* Suite du PWD avec ajout de "val/" */
    for(;!hors_liste(env); suivant(env))
    {
        valeur_elt(env,(void **)&val);
        pwd = realloc(pwd, sizeof(char) * (strlen(pwd) + strlen(val)) + 2);
        strcat(pwd,val);
        strcat(pwd,"/");
    }

    /* Mis à jour de WOD_PWD */
    WOD_PWD = pwd;

    free(project_name_min);
    return OK;
}

/**
 * \fn t_erreur creation_chemin (char * ajout, char ** res)
 * \brief Concatène 2 chaine de caractère.
 * \param ajout Chaine de caractère à ajouter à gauche de WOD_PWD.
 * \param res Chaine de caractère résultat.
 * \return Une erreur s'il y en a une.
*/
t_erreur creation_chemin (char * ajout, char ** res)
{
    /* Erreur : pointeur NULL */
    if (!ajout || !res) return PTR_NULL;

    /* Concaténation */
    *res = malloc(sizeof(char) * (strlen(WOD_PWD) + strlen(ajout) + 1));
    strcpy(*res, WOD_PWD);
    strcat(*res, ajout);

    return OK;
}

/**
 * \fn t_erreur tolower_str (char * str, char ** res)
 * \brief Met en minuscule une chaine de caractère.
 * \param str Chaine de caractère source.
 * \param res Chaine de caractère résultat.
 * \return Une erreur s'il y en a une.
*/
t_erreur tolower_str (char * str, char ** res)
{
    /* Erreur : pointeur NULL */
    if (!str || !res) return PTR_NULL;

    /* Mise en minuscule */
    *res = malloc(sizeof(char) * (strlen(str) + 1));
    int i;
    for (i = 0; str[i]; i++)
        (*res)[i] = tolower(str[i]);
    (*res)[i] = '\0';

    return OK;
}
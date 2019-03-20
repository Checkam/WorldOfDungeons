/**
 * \file json.c
 * \brief Module qui lit et écrit des fichiers au format JSON.
 * \author GALBRUN Tibane
 * \version 0.3
 * \date 5 Mars 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
#include <chemin.h>
#include <erreur.h>

/* Variables Globales */
/**
 * \var crt_car
 * \brief Variable globale contenant le dernier caractère ajouté au fichier JSON en cours.
 * \brief La variable est égale à '#' par défaut quand on est ni dans un fichier ni dans un objet;
*/
char crt_car = '#';

/*################################################
  ###### Création, Ouverture, Suppression, #######
  ########## Fermeture de Fichier JSON ###########
  ################################################*/

/**
 * \fn FILE * open_json (char * dossier, char * name, char * mode)
 * \brief Créer, s'il ne l'est pas, le fichier JSON et l'ouvre.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le json.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json'.
 * \param mode Mode d'ouverture du fichier.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * open_json (char * dossier, char * name, char * mode)
{
    /* Création chemin + nom_fichier */
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_json = concat_str (name,".json");

    /* Création et Ouverture Fichier */
    char * lieu = concat_str (chemin,name_json);
    FILE * file = fopen(lieu,mode);

    free(name_json);
    free(chemin);
    free(lieu);
    crt_car = '#';
    return file;
}

/**
 * \fn int del_json (char * dossier, char * name)
 * \brief Supprime un fichier JSON.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le json.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json' à supprimer.
 * \return Une erreur s'il y en a une.
*/
t_erreur del_json (char * dossier, char * name)
{
    char * chemin;
    creation_chemin(dossier, &chemin);
    char * name_json = concat_str (name,".json");
    char * lieu = concat_str (chemin,name_json);

    FILE * file = fopen(lieu,"r");
    fclose(file);
    if (file)
    {
        remove(lieu);
        free(name_json);
        free(chemin);
        free(lieu);
        return OK;
    }
    free(name_json);
    free(chemin);
    free(lieu);
    return REMOVE_FILE_ERROR;
}

/*################################################
  ############## Ecriture de Données #############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn t_erreur write_json (FILE * file, char * key, void * value, char * value_type)
 * \brief Ecrit une clé/valeur au format JSON dans un fichier.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu le couple clé/valeur 'key:value'.
 * \param file Le fichier ou écrire.
 * \param key La clé correspondant à la valeur.
 * \param value La valeur à écrire.
 * \param value_type Le type de la valeur à écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur write_json (FILE * file, char * key, void * value, char * value_type)
{
    /* FILE_ERROR */
    if (!file) return FILE_ERROR;
    /* PTR_NULL */
    if (!key || !value || !value_type) return PTR_NULL;

    if(crt_car != '{') fprintf(file,",");

    /* ENTIER */
    if (!strcmp(value_type,"d")) fprintf(file,"\"%s\":%d",key,*(int *)value);
    /* FLOAT */
    else if (!strcmp(value_type,"f")) fprintf(file,"\"%s\":%.2f",key,*(float *)value);
    /* STRING */
    else if (!strcmp(value_type,"s")) fprintf(file,"\"%s\":\"%s\"",key,(char *)value);
    /* U_INT */
    else if (!strcmp(value_type,"u")) fprintf(file,"\"%s\":%u",key,*(unsigned int *)value);
    else return TYPE_ERROR;

    crt_car = '#';

    return OK;
}

/**
 * \fn t_erreur open_json_obj (FILE * file)
 * \brief Démarre un nouvelle objet au format JSON dans un fichier.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu '{' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur open_json_obj (FILE * file)
{
    /* FILE_ERROR */
    if (!file) return FILE_ERROR;

    fprintf(file,"{");
    crt_car = '{';

    return OK;
}

/**
 * \fn int close_json_obj (FILE * file)
 * \brief Ferme l'objet JSON.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu '}' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur close_json_obj (FILE * file)
{
    /* FILE_ERROR */
    if (!file) return FILE_ERROR;

    fprintf(file,"}\n");
    crt_car = '#';

    return OK;
}

/*################################################
  ############## Lecture de Données ##############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn t_erreur extract_json_obj (FILE * file, char ** obj)
 * \brief Récupère un objet JSON dans un fichier.
 * \brief La lecture s'effectue dans le fichier 'file' et on récupère un objet.
 * \param file Le fichier à lire.
 * \param obj L'endroit ou enregistrer l'objet.
 * \return Une erreur s'il y en a une.
*/
t_erreur extract_json_obj (FILE * file, char ** obj)
{
    /* FILE_ERROR */
    if (!file) return FILE_ERROR;
    /* PTR_NULL */
    if (!obj) return PTR_NULL;

    int pas = 15, i = 0;
    while (crt_car != '{' && fscanf(file,"%c",&crt_car) != EOF);
    *obj = malloc(sizeof(char) * pas);
    (*obj)[i++] = crt_car;
    for (;crt_car != '}' && fscanf(file,"%c",&crt_car) != EOF; i++)
    {
        if (!(i%pas)) *obj = realloc(*obj, sizeof(char) * ((i/pas + 1) * pas) + 1);
        (*obj)[i] = crt_car;
    }
    (*obj)[i] = '\0';
    *obj = realloc(*obj, sizeof(char) * strlen(*obj) + 1);
    crt_car = '#';
    
    return OK;
}

/**
 * \fn t_erreur read_json_obj (FILE * file, char * key, void * value, char * value_type)
 * \brief Lit un objet JSON.
 * \brief La lecture s'effectue dans le fichier 'file' et on va chercher la valeur correspondant à la 'key'.
 * \param file Le fichier à lire.
 * \param key La clé à chercher.
 * \param value La valeur à modifier.
 * \param value_type Le type de la valeur recherché.
 * \return Une erreur s'il y en a une.
*/
t_erreur read_json_obj (char * obj, char * key, void * value, char * value_type)
{
    /* PTR_NULL */
    if (!key || !obj) return PTR_NULL;

    char * search;

    /* On cherche si la clé est présent dans l'objet JSON */
    search = strstr(obj,key);
    if (!search) return KEY_NOT_FOUND; /* KEY_NOT_FOUND */

    /* On récupère la valeur */
    char save_val[strlen(obj)];
    int i, j;
    for (i = search - obj + strlen(key) + 2, j = 0; obj[i] != ',' && obj[i] != '}'; i++, j++)
    {
        save_val[j] = obj[i];
        if (obj[i] == '"' && (obj[i+1] == ',' || obj[i+1] == '}')) j--;
    }
    save_val[j] = '\0';

    /* On traite la valeur */
    /* ENTIER */
    if (!strcmp(value_type,"d")) *(int *)value = atoi(save_val);
    /* ENTIER 8_T*/
    if (!strcmp(value_type,"d16")) *(int8_t *)value = atoi(save_val);
    /* ENTIER 16_T*/
    if (!strcmp(value_type,"d16")) *(int16_t *)value = atoi(save_val);
    /* ENTIER 32_T*/
    if (!strcmp(value_type,"d16")) *(int32_t *)value = atoi(save_val);
    /* ENTIER 64_T*/
    if (!strcmp(value_type,"d16")) *(int64_t *)value = atoi(save_val);
    /* FLOAT */
    else if (!strcmp(value_type,"f")) *(float *)value = atof(save_val);
    /* STRING */
    else if (!strcmp(value_type,"s")) strncpy((char *)value,save_val+1,sizeof(char) * strlen(save_val));
    /* U_INT */
    else if (!strcmp(value_type,"u")) *(unsigned int *)value = atoi(save_val);
    else return TYPE_ERROR;

    return OK;
}

/*################################################
  ############### Fonctions Autres ###############
  ################################################*/

/**
 * \fn char * concat_str (char * str1, char * str2)
 * \brief Concatène 2 chaine de caractère.
 * \param str1 Chaine de caractère de gauche.
 * \param str2 Chaine de caractère de droite.
 * \return Une chaine de caractère résultat de la concatènation.
*/
char * concat_str (char * str1, char * str2)
{
    char * str_res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    strcpy(str_res, str1);
    strcat(str_res, str2);
    return str_res;
}

/**
 * \fn t_erreur fstart (FILE * file)
 * \brief Remet le pointeur file au début du fichier.
 * \param str1 Chaine de caractère de gauche.
 * \return Une erreur s'il y en a une.
*/
t_erreur fstart (FILE * file)
{
    if (!file) return PTR_NULL;
    fseek(file, 0, SEEK_SET);
    return OK;
}
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
 * \fn FILE * new_json (char * name)
 * \brief Créer, s'il ne l'est pas, le fichier JSON et l'ouvre en écriture.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json'.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * new_json (char * name)
{
    char * name_json = concat_str (name,".json");
    FILE * file = fopen(name_json,"w");
    free(name_json);
    crt_car = '#';
    return file;
}

/**
 * \fn int del_json (char * name)
 * \brief Supprime un fichier JSON.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json' à supprimer.
 * \return Un entier valant 0 si tout c'est bien passé.
*/
int del_json (char * name)
{
    char * name_json = concat_str(name,".json");
    FILE * file = fopen(name_json,"r");
    fclose(file);
    if (file)
    {
        remove(name_json);
        free(name_json);
        return 0;
    }
    free(name_json);
    return 1;
}

/**
 * \fn FILE * open_json (char * name)
 * \brief Ouvre un fichier JSON en lecture.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json' à lire.
 * \return Un pointeur sur le fichier ouvert.
*/
FILE * open_json (char * name)
{
    char * name_json = concat_str(name,".json");
    FILE * file = fopen(name_json,"r");
    free(name_json);
    return file;
    
}

/*################################################
  ############## Ecriture de Données #############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn int write_json (FILE * file, char * key, void * value, char value_type)
 * \brief Ecrit une clé/valeur au format JSON dans un fichier.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu le couple clé/valeur 'key:value'.
 * \param file Le fichier ou écrire.
 * \param key La clé correspondant à la valeur.
 * \param value La valeur à écrire.
 * \param value_type Le type de la valeur à écrire.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int write_json (FILE * file, char * key, void * value, char value_type)
{
    /* FILE_ERROR */
    if (!file) return 1;
    /* VALUE_ERROR */
    if (!key || !value) return 2;

    if(crt_car != '{') fprintf(file,",");

    switch (value_type)
    {
        /* ENTIER */
        case 'd': fprintf(file,"\"%s\":%d",key,*(int *)value); break;
        /* FLOTTANT */
        case 'f': fprintf(file,"\"%s\":%.2f",key,*(float *)value); break;
        /* STRING */
        case 's': fprintf(file,"\"%s\":\"%s\"",key,(char *)value); break;
        /* TYPE_ERROR */
        default: return 1;
    }

    crt_car = '#';

    return 0;
}

/**
 * \fn int open_json_obj (FILE * file)
 * \brief Démarre un nouvelle objet au format JSON dans un fichier.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu '{' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int open_json_obj (FILE * file)
{
    /* FILE_ERROR */
    if (!file) return 1;

    fprintf(file,"{");
    crt_car = '{';

    return 0;
}

/**
 * \fn int close_json_obj (FILE * file)
 * \brief Ferme l'objet JSON.
 * \brief L'écriture s'effectue dans le fichier 'file' en ajout avec pour contenu '}' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int close_json_obj (FILE * file)
{
    /* FILE_ERROR */
    if (!file) return 1;

    fprintf(file,"}\n");
    crt_car = '#';

    return 0;
}

/*################################################
  ############## Lecture de Données ##############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn int extract_json_obj (FILE * file, char ** obj)
 * \brief Récupère un objet JSON dans un fichier.
 * \brief La lecture s'effectue dans le fichier 'file' et on récupère un objet.
 * \param file Le fichier à lire.
 * \param obj L'endroit ou enregistrer l'objet.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int extract_json_obj (FILE * file, char ** obj)
{
    /* FILE_ERROR */
    if (!file) return 1;
    /* PTR_VALUE_ERROR */
    if (!obj) return 1;
    *obj = malloc(sizeof(char) * LINE_MAX_WIDTH);
    fscanf(file,"%s\n",*obj);
    *obj = realloc(*obj, sizeof(char) * strlen(*obj) + 1);
    
    return 0;
}

/**
 * \fn int read_json (FILE * file, char * key, void * value, char value_type)
 * \brief Lit un objet JSON.
 * \brief La lecture s'effectue dans le fichier 'file' et on va chercher la valeur correspondant à la 'key'.
 * \param file Le fichier à lire.
 * \param key La clé à chercher.
 * \param value La valeur à modifier.
 * \param value_type Le type de la valeur recherché.
 * \return Un entier pour savoir si l'opération c'est bien passée.
*/
int read_json_obj (char * obj, char * key, void * value, char value_type)
{
    /* VALUE_ERROR */
    if (!key || !obj) return 1;

    char * search;

    /* On cherche si la clé est présent dans l'objet JSON */
    search = strstr(obj,key);
    if (!search) return 1; /* KEY_NOT_FOUND */

    /* On récupère la valeur */
    char save_val[strlen(obj)];
    int i, j;
    for (i = search - obj + strlen(key) + 2, j = 0; obj[i] != ',' && obj[i] != '}'; i++, j++)
    {
        save_val[j] = obj[i];
    }
    save_val[j] = '\0';

    /* On traite la valeur */
    switch (value_type)
    {
        /* ENTIER */
        case 'd' : *(int *)value = atoi(save_val); break;
        /* FLOAT */
        case 'f' : *(float *)value = atof(save_val); break;
        /* STRING */
        case 's' : strncpy((char *)value,save_val+1,sizeof(char) * strlen(save_val) - 2); break;
        /* TYPE_ERROR */
        default : return 1;
    }

    return 0;
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
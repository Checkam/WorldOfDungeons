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
#include <fichier.h>
#include <stdint.h>
#include <inttypes.h>
#include <liste.h>

/* Variables Globales */
/**
 * \var crt_car
 * \brief Variable globale contenant le dernier caractère ajouté au fichier JSON en cours.
 * \brief La variable est égale à '#' par défaut quand on est ni dans un fichier ni dans un objet;
*/
char crt_car = '#';

char * save_dossier; // Sauvegarde du dossier où se trouve le fichier JSON.
char * save_name; // Sauvegarde du nom du fichier JSON.
uint8_t object_open = 0; // Indique si un objet est ouvert (en cours d'écriture).

/*################################################
  ###### Création, Ouverture, Suppression, #######
  ########## Fermeture de Fichier JSON ###########
  ################################################*/

/**
 * \fn t_erreur JSON_Open (char * dossier, char * name, char * mode)
 * \brief Créer, s'il ne l'est pas, le fichier JSON et l'ouvre.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le json.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json'.
 * \param mode Mode d'ouverture du fichier.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Open (char * dossier, char * name, char * mode)
{
    if (object_open) return FILE_ERROR;
    crt_car = '#';
    t_json file;
    file = open_file(dossier,name,".json",mode);
    if (!file) return OPEN_FILE_ERROR;
    object_open = 0;

    /* Récup contenu du fichier */
    fstart(file);
    init_liste(&json_objects);
    char * obj;
    for (en_tete(&json_objects); JSON_Extract_Object(file,&obj) != FILE_ERROR; suivant(&json_objects))
    {
        ajout_droit(&json_objects,obj);
    }
    fclose(file);

    /* Save dossier et nom fichier */
    save_dossier = malloc(strlen(dossier) + 1);
    save_name = malloc(strlen(name) + 1);
    strcpy(save_dossier,dossier);
    strcpy(save_name,name);

    return OK;
}

/**
 * \fn int JSON_Delete (char * dossier, char * name)
 * \brief Supprime un fichier JSON.
 * \param dossier Chaine de caractère représentant le dossier ou se trouve le json.
 * \param name Chaine de caractère représenant le nom du fichier sans le '.json' à supprimer.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Delete (char * dossier, char * name)
{
    return del_file(dossier,name,".json");
}

/**
 * \fn t_erreur JSON_Close ()
 * \brief Ferme un fichier JSON.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Close ()
{
    if (object_open) return FILE_ERROR;
    t_json file;

    /* Ouverture du fichier pour enregistrement */
    file = open_file(save_dossier,save_name,".json","w");
    if (!file) return OPEN_FILE_ERROR;
    object_open = 0;

    /* Enregistrement */
    char * obj;
    for (en_tete(&json_objects); !hors_liste(&json_objects); suivant(&json_objects))
    {
        valeur_elt(&json_objects,(void **)&obj);
        fprintf(file,"%s\n",obj);
    }

    /* Suppression de la liste */
    detruire_liste(&json_objects,free);

    /* Fermeture du fichier */
    fclose(file);
    file = NULL;

    /* Suppression nom et dossier du fichier */
    free(save_dossier);
    save_dossier = NULL;
    free(save_name);
    save_name = NULL;

    return OK;
}

/*################################################
  ############## Ecriture de Données #############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn t_erreur JSON_Write (char * key, void * value, char * value_type)
 * \brief Ecrit une clé/valeur au format JSON dans une liste.
 * \param key La clé correspondant à la valeur.
 * \param value La valeur à écrire.
 * \param value_type Le type de la valeur à écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Write (char * key, void * value, char * value_type)
{
    /* FILE_ERROR */
    if (!object_open) return FILE_ERROR;
    /* PTR_NULL */
    if (!key || !value || !value_type) return PTR_NULL;

    char * obj;
    valeur_elt(&json_objects,(void **)&obj);
    oter_elt(&json_objects,NULL);
    char * new_obj;
    int taille = sizeof(char) * (strlen(key) + strlen(obj) + 10);
    new_obj = malloc(taille);

    if(crt_car != '{') sprintf(new_obj,"%s,",obj);
    else sprintf(new_obj,"%s",obj);

    /* ENTIER */
    if (!strcmp(value_type,"d"))
    {
        taille += sizeof(char) * 6;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%d",new_obj,key,*(int *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"d8"))
    {
        taille += sizeof(char) * 4;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRId8"",new_obj,key,*(int8_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"d16"))
    {
        taille += sizeof(char) * 6;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRId16"",new_obj,key,*(int16_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"d32"))
    {
        taille += sizeof(char) * 11;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRId32"",new_obj,key,*(int32_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"d64"))
    {
        taille += sizeof(char) * 20;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRId64"",new_obj,key,*(int64_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    /* FLOAT */
    else if (!strcmp(value_type,"f"))
    {
        taille += sizeof(char) * 11;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%f",new_obj,key,*(float *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    /* STRING */
    else if (!strcmp(value_type,"s"))
    {
        taille += sizeof(char) * strlen((char *)value);
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":\"%s\"",new_obj,key,(char *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    /* U_INT */
    else if (!strcmp(value_type,"u"))
    {
        taille += sizeof(char) * 5;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%u",new_obj,key,*(unsigned int *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"u8"))
    {
        taille += sizeof(char) * 3;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRIu8"",new_obj,key,*(uint8_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"u16"))
    {
        taille += sizeof(char) * 5;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRIu16"",new_obj,key,*(uint16_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"u32"))
    {
        taille += sizeof(char) * 10;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRIu32"",new_obj,key,*(uint32_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else if (!strcmp(value_type,"u64"))
    {
        taille += sizeof(char) * 20;
        obj = realloc(obj,taille);
        sprintf(obj,"%s\"%s\":%"PRIu64"",new_obj,key,*(uint64_t *)value);
        free(new_obj);
        ajout_droit(&json_objects,obj);
    }
    else
    {
        free(new_obj);
        return TYPE_ERROR;
    }

    crt_car = '#';

    return OK;
}

/**
 * \fn t_erreur JSON_Open_Object ()
 * \brief Démarre un nouvel objet au format JSON dans une liste.
 * \brief Le contenu est '{' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Open_Object ()
{
    /* FILE_ERROR */
    if (object_open) return FILE_ERROR;
    object_open = 1;

    char * obj = malloc(sizeof(char) * 2);
    sprintf(obj,"{");
    crt_car = '{';

    en_queue(&json_objects);
    ajout_droit(&json_objects,obj);
    en_queue(&json_objects);

    return OK;
}

/**
 * \fn t_erreur JSON_Close_Object ()
 * \brief Ferme l'objet JSON.
 * \brief Le contenu est '}' et la variable crt_car est mis à jour.
 * \param file Le fichier ou écrire.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Close_Object ()
{
    /* FILE_ERROR */
    if (!object_open) return FILE_ERROR;
    object_open = 0;

    en_queue(&json_objects);
    char * obj;
    valeur_elt(&json_objects,(void **)&obj);
    oter_elt(&json_objects,NULL);

    int taille = strlen(obj) + 2 * sizeof(char);
    obj = realloc(obj,taille);
    obj[taille-2] = '}';
    obj[taille-1] = '\0';
    ajout_droit(&json_objects,obj);
    crt_car = '#';

    return OK;
}

/*################################################
  ############## Lecture de Données ##############
  ################ au Format JSON ################
  ################################################*/

/**
 * \fn t_erreur JSON_Extract_Object (t_json file, char ** obj)
 * \brief Récupère un objet JSON dans un fichier.
 * \brief La lecture s'effectue dans le fichier 'file' et on récupère un objet.
 * \param file Le fichier à lire.
 * \param obj L'endroit ou enregistrer l'objet.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Extract_Object (t_json file, char ** obj)
{
    /* FILE_ERROR */
    if (!file) return FILE_ERROR;
    /* PTR_NULL */
    if (!obj) return PTR_NULL;

    int pas = 15, i = 0;
    while (crt_car != '{' && fscanf(file,"%c",&crt_car) != EOF);
    if (feof(file)) return FILE_ERROR;
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
 * \fn t_erreur JSON_Read_Object (char * obj, char * key, void * value, char * value_type)
 * \brief Lit un objet JSON.
 * \brief La lecture s'effectue dans l'objet 'obj' et on va chercher la valeur correspondant à la 'key'.
 * \param obj L'objet à lire.
 * \param key La clé à chercher.
 * \param value La valeur à modifier.
 * \param value_type Le type de la valeur recherché.
 * \return Une erreur s'il y en a une.
*/
t_erreur JSON_Read_Object (char * obj, char * key, void * value, char * value_type)
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
    if (!strcmp(value_type,"d8")) *(int8_t *)value = atoi(save_val);
    if (!strcmp(value_type,"d16")) *(int16_t *)value = atoi(save_val);
    if (!strcmp(value_type,"d32")) *(int32_t *)value = atol(save_val);
    if (!strcmp(value_type,"d64")) *(int64_t *)value = atoll(save_val);
    /* FLOAT */
    else if (!strcmp(value_type,"f")) *(float *)value = atof(save_val);
    /* STRING */
    else if (!strcmp(value_type,"s")) strncpy((char *)value,save_val+1,sizeof(char) * strlen(save_val));
    /* U_INT */
    else if (!strcmp(value_type,"u")) *(unsigned int *)value = strtoull(save_val,NULL,0);
    else if (!strcmp(value_type,"u8")) *(uint8_t *)value = strtoull(save_val,NULL,0);
    else if (!strcmp(value_type,"u16")) *(uint16_t *)value = strtoull(save_val,NULL,0);
    else if (!strcmp(value_type,"u32")) *(uint32_t *)value = strtoull(save_val,NULL,0);
    else if (!strcmp(value_type,"u64")) *(uint64_t *)value = strtoull(save_val,NULL,0);
    else return TYPE_ERROR;

    return OK;
}

/*################################################
  ############### Fonctions Autres ###############
  ################################################*/

/**
 * \fn t_erreur fstart (t_json file)
 * \brief Remet le pointeur file au début du fichier.
 * \param file Le fichier où repartir du début.
 * \return Une erreur s'il y en a une.
*/
t_erreur fstart (t_json file)
{
    if (!file) return FILE_ERROR;
    fseek(file, 0, SEEK_SET);
    return OK;
}
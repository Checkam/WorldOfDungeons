/**
*   \file map.c
*   \brief Module permettant de géré une map (Création,Suppression)
*   \author {Maxence.D}
*   \version 0.1 
*   \date 07 mars 2019 
**/

#ifndef __MAP_H__
#define __MAP_H__
#include <erreur.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>


/**
    \fn t_map * MAP_creer(char * nom_map, int SEED)
    \brief Créer une map
    \param nom_map Le nom de la map
    \param SEED Le SEED de génération de la map
    \return renvoie le pointeur correspondant
**/
t_map * MAP_creer(char * nom_map, int SEED) {

    t_map *map  = malloc(sizeof(t_map));
    map->nom = malloc(sizeof(char) * strlen(nom_map) + 1);
    strcpy(map->nom,nom_map);
    map->SEED = SEED;

    MAP_creer_dir(map);

    return map;
}

/**
    \fn t_erreur MAP_creer_dir(t_map * map)
    \brief Créer le repertoire d'une map
    \param map Pointeur sur la map dont le repertoire doit être créer 
    \return renvoie un code erreur (OK,POINTEUR_NULL)
**/
t_erreur MAP_creer_dir(t_map * map) {
    if(map == NULL) return PTR_NULL;

    char * path_dir = malloc(sizeof(char) * strlen(map->nom) + sizeof(char) * strlen(PATH_MAP_DIR));
    strcpy(path_dir,PATH_MAP_DIR);
    strcat(path_dir,map->nom);
    mkdir(path_dir,755);

    return OK;
}

/**
    \fn t_erreur MAP_supprimer_dir(t_map * map)
    \brief Supprimer le repertoire d'une map
    \param map Pointeur sur la map dont le repertoire doit être supprimer 
    \return renvoie le pointeur correspondant
**/
t_erreur MAP_supprimer_dir(t_map * map) {
    if(map == NULL) return PTR_NULL;

    char * path_dir = malloc(sizeof(char) * strlen(map->nom) + sizeof(char) * strlen(PATH_MAP_DIR));
    strcpy(path_dir,PATH_MAP_DIR);
    strcat(path_dir,map->nom);
    rmdir(path_dir);

    return OK;
}

/**
    \fn t_erreur MAP_supprimer(t_map ** map)
    \brief Supprime un pointeur t_map
    \param map Pointeur de pointeur de t_map à supprimer et mettre a NULL
    \return renvoie le pointeur correspondant
**/
t_erreur MAP_supprimer(t_map ** map) {
    if(map == NULL) return PTR_NULL;

    if((*map)->nom != NULL){
        free((*map)->nom);
        (*map)->nom = NULL;
    }
    free(*map);
    map = NULL;
    return OK;
}



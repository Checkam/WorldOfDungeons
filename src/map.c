/**
*   \file map.c
*   \brief Module permettant de géré une map (Création,Suppression)
*   \author {Maxence.D}
*   \version 0.1 
*   \date 07 mars 2019 
**/
#include <erreur.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map.h>

/**
    \fn t_map * MAP_creer(char * nom_map, int SEED)
    \brief Créer une map
    \param nom_map Le nom de la map
    \param SEED Le SEED de génération de la map
    \return renvoie le pointeur correspondant
**/
t_map * MAP_creer(char * nom_map, int SEED){
    t_map *map  = malloc(sizeof(t_map));
    map->nom = malloc(sizeof(char) * strlen(nom_map) + 1);
    strcpy(map->nom,nom_map);
    map->SEED = SEED;
    return map;
}

/**
    \fn t_erreur MAP_supprimer_dir(t_map * map)
    \brief Supprimer le repertoire d'une map
    \param map Pointeur sur la map dont le repertoire doit être supprimer 
    \return renvoie le pointeur correspondant
**/
t_erreur MAP_supprimer_dir(t_map * map){

    return OK;
}

/**
    \fn t_erreur MAP_supprimer(t_map ** map)
    \brief Supprime un pointeur t_map
    \param map Pointeur de pointeur de t_map à supprimer et mettre a NULL
    \return renvoie le pointeur correspondant
**/
t_erreur MAP_supprimer(t_map ** map){
    if(map == NULL) return PTR_VALUE_ERROR;
    if((*map)->nom != NULL){
        free((*map)->nom);
        (*map)->nom = NULL;
    }
    free(*map);
    map = NULL;
    return OK;
}



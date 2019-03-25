/**
 *   \file map.h
 *   \brief Module permettant de géré une map
 *   \author {Maxence.D}
 *   \version 0.1
 *   \date 10 mars 2019
 **/
#ifndef __MAP_H__
#define __MAP_H__

#include <erreur.h>
#include <liste.h>
#include <block.h>

#define PATH_MAP_DIR "data/map/"

/**
 \struct t_map
 \brief Structure map
**/
typedef struct s_map {
    char * nom;
    int SEED;
    t_liste *list;
} t_map;

t_erreur MAP_creer(t_map ** map, char * nom_map, int SEED) ;
t_erreur MAP_charger(t_map ** map, char * nom_map);
t_erreur MAP_detruction(t_map ** map);

t_erreur MAP_creer_dir(t_map * map);
t_erreur MAP_supprimer(t_map * map);

t_erreur MAP_sauvegarder(t_map * map);

char * MAP_creer_path(char * nom_map);
t_erreur MAP_detruire_path(char ** path_dir);

t_block *MAP_GetBlockFromList(t_map *map, int x, int y);

#endif

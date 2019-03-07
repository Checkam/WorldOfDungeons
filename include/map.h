
#ifndef __MAP_H__
#define __MAP_H__

#include <erreur.h>
#endif

#define PATH_MAP_DIR "map/"

/**
 \struct t_map
 \brief Structure map
**/
typedef struct s_map {
    char * nom;
    int SEED;
    // Une liste
} t_map; 

t_map * MAP_creer(char * nom_map, int SEED);
t_erreur MAP_supprimer(t_map ** map);

t_erreur MAP_creer_dir(t_map * map);
t_erreur MAP_supprimer_dir(t_map * map);
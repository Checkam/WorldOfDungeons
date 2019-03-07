
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

t_erreur MAP_creer(t_map ** map, char * nom_map, int SEED) ;
t_erreur MAP_charger(t_map ** map, char * nom_map);
t_erreur MAP_detruction(t_map ** map);

t_erreur MAP_creer_dir(t_map * map);
t_erreur MAP_supprimer(t_map * map);

t_erreur MAP_sauvegarder(t_map * map);

char * MAP_creer_path(t_map * map);
t_erreur MAP_detruire_path(char ** path_dir);
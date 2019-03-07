
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
t_erreur MAP_supprimer_dir(t_map * map);
t_erreur MAP_supprimer(t_map ** map);
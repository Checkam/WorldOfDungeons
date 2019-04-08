#include <item.h>

#include <assert.h>
#include <liste.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <outils_SDL.h>

static void default_item_drop ();
static void default_item_type ();

t_block_drop *tabItemDrop = NULL;

t_liste_item *item;

uint8_t init_item( SDL_Renderer *renderer ) {

    if ( tabItemDrop )
        return 1;

    tabItem = NULL;

    uint16_t i;

    tabItemDrop = malloc( sizeof( t_block_drop ) * NB_BLOCK );

    for ( i = 0 ; i < NB_BLOCK ; i++ ) {

        ( tabItemDrop + i )->id = i;
        ( tabItemDrop + i )->drop = NULL; /* aka aucun drop */
    }

    default_item_drop();

    tabItem = malloc( sizeof( t_item_type ) * (I_END + 1) );

    default_item_type(renderer);

    srand(time(NULL));

    return 0;
}

uint8_t block_to_item ( t_materiaux materiaux, t_liste_item **item ) {

    uint8_t nbItem;

    #ifdef DEBUG
        if ( materiaux < 0 || materiaux > NB_BLOCK )
            return 1;
    #endif

    if ( ( tabItemDrop + materiaux )->drop == NULL ) {

        nbItem = 0;
        item = NULL;
        return 0;
    }

    uint8_t i = 0;
    uint16_t aleatoire;

    while ( (( tabItemDrop + materiaux )->drop + i)->item != I_END )
        i++;

    i++;

    if ( *item )
        free(*item);

    (*item) = malloc( sizeof(t_liste_item) * i );

    #ifdef DEBUG
        if ( *item == NULL )
            return 2;
    #endif

    i = 0, nbItem = 0;

    while ( (( tabItemDrop + materiaux )->drop + i)->item != I_END ) {

        aleatoire = rand();
        while  ( aleatoire >= 32000 )
            aleatoire = rand();
        aleatoire %= 1000;

        if ( aleatoire < (( tabItemDrop + materiaux )->drop + i)->pourMille ) {

            ( *item + nbItem )->nbDrop = (( tabItemDrop + materiaux )->drop + i)->nombre;
            ( *item + nbItem )->item = (( tabItemDrop + materiaux )->drop + i)->item;
            nbItem++;
        }

        switch ( (( tabItemDrop + materiaux )->drop + i)->besoin ) {
            case PAS_DROP_APRES_N:
                if ( aleatoire < (( tabItemDrop + materiaux )->drop + i)->pourMille )
                    i += (( tabItemDrop + materiaux )->drop + i)->info;
                break;
        }

        i++;
    }

    ( *item + nbItem )->item = I_END;

    return 0;
}

void casser_block( t_materiaux materiaux, t_liste **listeItem ) {

    t_liste_item *totalItem = NULL;
    t_liste_item *temp;

    block_to_item( materiaux, &totalItem );

    printf("apres block to item\n");

    uint16_t i = 0;

    while ( ( totalItem + i )->item != I_END ) {

	    printf("	%d fois %d\n", ( totalItem + i )->nbDrop, ( totalItem + i )->item );
        temp = malloc( sizeof(t_liste_item));
        temp->item = (totalItem + i)->item;
        temp->nbDrop = (totalItem + i)->nbDrop;
        ajout_droit(*listeItem, (void *)temp);
		i++;
    }

    en_tete(*listeItem);
    t_liste_item *test;

    while ( !hors_liste(*listeItem) ) {
        valeur_elt(*listeItem, (void **)&test );
        printf("%d, %d\n", test->item, test->nbDrop );
        suivant(*listeItem);
    }

    free(totalItem);
}

void exit_item( t_liste_item **item ) {

    free( ( tabItemDrop + HERBE )->drop);
    free( ( tabItemDrop + TERRE )->drop);
    free( ( tabItemDrop + SABLE )->drop);
    free( ( tabItemDrop + FEUILLE )->drop);
    free( ( tabItemDrop + BOIS )->drop);
    free( ( tabItemDrop + ROCHE )->drop);
    free( ( tabItemDrop + NEIGE )->drop);
    free( ( tabItemDrop + DIAMAND )->drop);
    free( ( tabItemDrop + GRAVIER )->drop);

    if ( *item != NULL )
        free(*item);

    free(tabItemDrop);
    free(tabItem);
    tabItemDrop = NULL;
}

static void default_item_drop () {
    /* pour l'instant ici, ce sera fait dans des fichiers json de tib a l'avenir */

    /* AIR */
    /* rien a change car aucun drop donc pointeur drop a NULL */


    /* HERBE */
    ( tabItemDrop + HERBE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    /*---------------------------------------------------------------
    *             | le bloc |                                    |qte |
    *             |qui doit |                                    |de  |
    *             |etre drop|                                    |drop|
    */
    ( tabItemDrop + HERBE )->drop->item = I_TERRE;
    ( tabItemDrop + HERBE )->drop->nombre = 1;
    ( tabItemDrop + HERBE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + HERBE )->drop->info = 0;
    ( tabItemDrop + HERBE )->drop->pourMille = 1000;

    (( tabItemDrop + HERBE )->drop + 1 )->item = I_END;

    /* TERRE */
    ( tabItemDrop + TERRE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + TERRE )->drop->item = I_TERRE;
    ( tabItemDrop + TERRE )->drop->nombre = 1;
    ( tabItemDrop + TERRE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + TERRE )->drop->info = 0;
    ( tabItemDrop + TERRE )->drop->pourMille = 1000;

    (( tabItemDrop + TERRE )->drop + 1 )->item = I_END;


    /* EAU */


    /* SABLE */
    ( tabItemDrop + SABLE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + SABLE )->drop->item = I_SABLE;
    ( tabItemDrop + SABLE )->drop->nombre = 1;
    ( tabItemDrop + SABLE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + SABLE )->drop->info = 0;
    ( tabItemDrop + SABLE )->drop->pourMille = 1000;

    (( tabItemDrop + SABLE )->drop + 1)->item = I_END;


    /* FEUILLE */
    ( tabItemDrop + FEUILLE )->drop = malloc( sizeof(t_liste_drop) * 3 );

    ( tabItemDrop + FEUILLE )->drop->item = I_POUSSE_ARBRE;
    ( tabItemDrop + FEUILLE )->drop->nombre = 1;
    ( tabItemDrop + FEUILLE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + FEUILLE )->drop->info = 0;
    ( tabItemDrop + FEUILLE )->drop->pourMille = 150; /* 15% de chance de drop */

    (( tabItemDrop + FEUILLE )->drop + 1 )->item = I_POMME;
    (( tabItemDrop + FEUILLE )->drop + 1 )->nombre = 1;
    (( tabItemDrop + FEUILLE )->drop + 1 )->besoin = AUCUN_BESOIN;
    (( tabItemDrop + FEUILLE )->drop + 1 )->info = 0;
    (( tabItemDrop + FEUILLE )->drop + 1 )->pourMille = 50; /* 5% de chance de drop */

    (( tabItemDrop + FEUILLE )->drop + 2 )->item = I_END;


    /* BOIS */
    ( tabItemDrop + BOIS )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + BOIS )->drop->item = I_BOIS;
    ( tabItemDrop + BOIS )->drop->nombre = 1;
    ( tabItemDrop + BOIS )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + BOIS )->drop->info = 0;
    ( tabItemDrop + BOIS )->drop->pourMille = 1000;

    (( tabItemDrop + BOIS )->drop + 1 )->item = I_END;


    /* ROCHE */
    ( tabItemDrop + ROCHE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + ROCHE )->drop->item = I_PIERRE;
    ( tabItemDrop + ROCHE )->drop->nombre = 1;
    ( tabItemDrop + ROCHE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + ROCHE )->drop->info = 0;
    ( tabItemDrop + ROCHE )->drop->pourMille = 1000;

    (( tabItemDrop + ROCHE )->drop + 1 )->item = I_END;


    /* NEIGE */
    ( tabItemDrop + NEIGE )->drop = malloc( sizeof(t_liste_drop) * 4 );

    ( tabItemDrop + NEIGE )->drop->item = I_BOULE_NEIGE;
    ( tabItemDrop + NEIGE )->drop->nombre = 1;
    ( tabItemDrop + NEIGE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + NEIGE )->drop->info = 0;
    ( tabItemDrop + NEIGE )->drop->pourMille = 1000; /* 1 boule de neige sur */

    (( tabItemDrop + NEIGE )->drop + 1 )->item = I_BOULE_NEIGE;
    (( tabItemDrop + NEIGE )->drop + 1 )->nombre = 1;
    (( tabItemDrop + NEIGE )->drop + 1 )->besoin = AUCUN_BESOIN;
    (( tabItemDrop + NEIGE )->drop + 1 )->info = 0;
    (( tabItemDrop + NEIGE )->drop + 1 )->pourMille = 200;

    (( tabItemDrop + NEIGE )->drop + 2 )->item = I_BOULE_NEIGE;
    (( tabItemDrop + NEIGE )->drop + 2 )->nombre = 1;
    (( tabItemDrop + NEIGE )->drop + 2 )->besoin = AUCUN_BESOIN;
    (( tabItemDrop + NEIGE )->drop + 2 )->info = 0;
    (( tabItemDrop + NEIGE )->drop + 2 )->pourMille = 200;

    (( tabItemDrop + NEIGE )->drop + 3 )->item = I_END;


    /* GLACE */


    /* DIAMAND */
    ( tabItemDrop + DIAMAND )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + DIAMAND )->drop->item = I_DIAMAND;
    ( tabItemDrop + DIAMAND )->drop->nombre = 1;
    ( tabItemDrop + DIAMAND )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + DIAMAND )->drop->info = 0;
    ( tabItemDrop + DIAMAND )->drop->pourMille = 1000;

    (( tabItemDrop + DIAMAND )->drop + 1 )->item = I_END;


    /* GRAVIER */

    ( tabItemDrop + GRAVIER )->drop = malloc( sizeof(t_liste_drop) * 3 );

    ( tabItemDrop + GRAVIER )->drop->item = I_SILEX;
    ( tabItemDrop + GRAVIER )->drop->nombre = 1;
    ( tabItemDrop + GRAVIER )->drop->besoin = PAS_DROP_APRES_N;
    ( tabItemDrop + GRAVIER )->drop->info = 1;
    ( tabItemDrop + GRAVIER )->drop->pourMille = 50;

    (( tabItemDrop + GRAVIER )->drop + 1 )->item = I_GRAVIER;
    (( tabItemDrop + GRAVIER )->drop + 1 )->nombre = 1;
    (( tabItemDrop + GRAVIER )->drop + 1 )->besoin = AUCUN_BESOIN;
    (( tabItemDrop + GRAVIER )->drop + 1 )->info = 0;
    (( tabItemDrop + GRAVIER )->drop + 1 )->pourMille = 1000;

    (( tabItemDrop + GRAVIER )->drop + 2 )->item = I_END;
}

static void default_item_type ( SDL_Renderer *renderer ) {

    char *chemin;
    SDL_Surface *surface = NULL;

    ( tabItem + I_TERRE )->nomItem = "terre";
    ( tabItem + I_TERRE )->stack = 50;
    ( tabItem + I_TERRE )->posable = NULL;
    if ( renderer ) {
        creation_chemin("data/Image/Terre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &(( tabItem + I_TERRE )->texture));
        free(chemin);
    } else
        (( tabItem + I_TERRE )->texture) = NULL;

    ( tabItem + I_PIERRE )->nomItem = "pierre";
    ( tabItem + I_PIERRE )->stack = 25;
    ( tabItem + I_PIERRE )->posable = NULL;
    if ( renderer ) {
        creation_chemin("data/Image/Pierre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_PIERRE )->texture);
        free(chemin);
    } else
        ( tabItem + I_PIERRE )->texture = NULL;

    ( tabItem + I_ROCHE )->nomItem = "roche";
    ( tabItem + I_ROCHE )->stack = 40;
    ( tabItem + I_ROCHE )->posable = NULL;
    if ( renderer ) {
        creation_chemin("data/Image/Roche_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_ROCHE )->texture);
        free(chemin);
    } else
        ( tabItem + I_ROCHE )->texture = NULL;

    ( tabItem + I_SABLE )->nomItem = "sable";
    ( tabItem + I_SABLE )->stack = 50;
    ( tabItem + I_SABLE )->posable = NULL;
    if ( renderer ) {
        creation_chemin("data/Image/Sable_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_SABLE )->texture);
        free(chemin);
    } else
        ( tabItem + I_SABLE )->texture = NULL;

    ( tabItem + I_GRAVIER )->nomItem = "gravier";
    ( tabItem + I_GRAVIER )->stack = 50;
    ( tabItem + I_GRAVIER )->posable = NULL;
    ( tabItem + I_GRAVIER )->texture = NULL;

    ( tabItem + I_BOIS )->nomItem = "bois brut";
    ( tabItem + I_BOIS )->stack = 40;
    ( tabItem + I_BOIS )->posable = NULL;
    ( tabItem + I_BOIS )->texture = NULL;

    ( tabItem + I_POUSSE_ARBRE )->nomItem = "pousse d'arbre";
    ( tabItem + I_POUSSE_ARBRE )->stack = 50;
    ( tabItem + I_POUSSE_ARBRE )->posable = NULL;
    ( tabItem + I_POUSSE_ARBRE )->texture = NULL;

    ( tabItem + I_POMME )->nomItem = "pomme";
    ( tabItem + I_POMME )->stack = 50;
    ( tabItem + I_POMME )->posable = NULL;
    ( tabItem + I_POMME )->texture = NULL;

    ( tabItem + I_BOULE_NEIGE )->nomItem = "boule de neige";
    ( tabItem + I_BOULE_NEIGE )->stack = 75;
    ( tabItem + I_BOULE_NEIGE )->posable = NULL;
    if ( renderer ) {
        creation_chemin("data/Image/Boule_de_neige_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_BOULE_NEIGE )->texture);
        free(chemin);
    } else
        ( tabItem + I_BOULE_NEIGE )->texture = NULL;
    
    ( tabItem + I_SILEX )->nomItem = "silex";
    ( tabItem + I_SILEX )->stack = 75;
    ( tabItem + I_SILEX )->posable = NULL;
    ( tabItem + I_SILEX )->texture = NULL;

    ( tabItem + I_DIAMAND )->nomItem = "diamant";
    ( tabItem + I_DIAMAND )->stack = 25;
    ( tabItem + I_DIAMAND )->posable = NULL;
    ( tabItem + I_DIAMAND )->texture = NULL;

    ( tabItem + I_END )->nomItem = "end";
    ( tabItem + I_END )->stack = 0;
    ( tabItem + I_END )->posable = NULL;
    ( tabItem + I_END )->texture = NULL;
    
    /*free(chemin);*/
    SDL_FreeSurface(surface);
}
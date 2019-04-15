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

    uint16_t i = 0;

    while ( ( totalItem + i )->item != I_END ) {

        temp = malloc( sizeof(t_liste_item));
        /* ne pas free temp ici, sinon l'objet de la liste sera free et ne sera plus recuperable */
        temp->item = (totalItem + i)->item;
        temp->nbDrop = (totalItem + i)->nbDrop;
        ajout_droit(*listeItem, (void *)temp);
		i++;
    }

    free(totalItem);
}

void exit_item( t_liste_item **item ) {

    uint16_t i;

    for ( i = 0 ; i < I_END ; i++ )
        if ( ( tabItem + i )->texture != NULL )
            SDL_DestroyTexture(( tabItem + i )->texture);

    for ( i = 0 ; i < NB_BLOCK ; i++ )
        if ( ( tabItemDrop + i )->drop != NULL )
            free( ( tabItemDrop + i )->drop );

    if ( item != NULL)
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


    /* BRIQUE */
    ( tabItemDrop + BRIQUE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + BRIQUE )->drop->item = I_BRIQUE;
    ( tabItemDrop + BRIQUE )->drop->nombre = 1;
    ( tabItemDrop + BRIQUE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + BRIQUE )->drop->info = 0;
    ( tabItemDrop + BRIQUE )->drop->pourMille = 1000;

    (( tabItemDrop + BRIQUE )->drop + 1)->item = I_END;


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
    ( tabItemDrop + MINERAI_DIAMAND )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_DIAMAND )->drop->item = I_DIAMAND;
    ( tabItemDrop + MINERAI_DIAMAND )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_DIAMAND )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_DIAMAND )->drop->info = 0;
    ( tabItemDrop + MINERAI_DIAMAND )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_DIAMAND )->drop + 1 )->item = I_END;


    /* FER */
    ( tabItemDrop + MINERAI_FER )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_FER )->drop->item = I_MINERAI_FER;
    ( tabItemDrop + MINERAI_FER )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_FER )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_FER )->drop->info = 0;
    ( tabItemDrop + MINERAI_FER )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_FER )->drop + 1 )->item = I_END;


    /* CUIVRE */
    ( tabItemDrop + MINERAI_CUIVRE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_CUIVRE )->drop->item = I_MINERAI_CUIVRE;
    ( tabItemDrop + MINERAI_CUIVRE )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_CUIVRE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_CUIVRE )->drop->info = 0;
    ( tabItemDrop + MINERAI_CUIVRE )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_CUIVRE )->drop + 1 )->item = I_END;


    /* ARGENT */
    ( tabItemDrop + MINERAI_ARGENT )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_ARGENT )->drop->item = I_MINERAI_ARGENT;
    ( tabItemDrop + MINERAI_ARGENT )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_ARGENT )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_ARGENT )->drop->info = 0;
    ( tabItemDrop + MINERAI_ARGENT )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_ARGENT )->drop + 1 )->item = I_END;


    /* OR */
    ( tabItemDrop + MINERAI_OR )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_OR )->drop->item = I_MINERAI_OR;
    ( tabItemDrop + MINERAI_OR )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_OR )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_OR )->drop->info = 0;
    ( tabItemDrop + MINERAI_OR )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_OR )->drop + 1 )->item = I_END;


    /* CHARBON */
    ( tabItemDrop + MINERAI_CHARBON )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + MINERAI_CHARBON )->drop->item = I_CHARBON;
    ( tabItemDrop + MINERAI_CHARBON )->drop->nombre = 1;
    ( tabItemDrop + MINERAI_CHARBON )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + MINERAI_CHARBON )->drop->info = 0;
    ( tabItemDrop + MINERAI_CHARBON )->drop->pourMille = 1000;

    (( tabItemDrop + MINERAI_CHARBON )->drop + 1 )->item = I_END;


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

    ( tabItem + I_TERRE )->id = I_TERRE;
    ( tabItem + I_TERRE )->nomItem = "terre";
    ( tabItem + I_TERRE )->stack = 50;
    ( tabItem + I_TERRE )->posable = TERRE;
    if ( renderer ) {
        creation_chemin("data/Image/Terre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &(( tabItem + I_TERRE )->texture));
        free(chemin);
    } else
        (( tabItem + I_TERRE )->texture) = NULL;

    ( tabItem + I_PIERRE )->id = I_TERRE;
    ( tabItem + I_PIERRE )->nomItem = "pierre";
    ( tabItem + I_PIERRE )->stack = 25;
    ( tabItem + I_PIERRE )->posable = ROCHE;
    if ( renderer ) {
        creation_chemin("data/Image/Pierre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_PIERRE )->texture);
        free(chemin);
    } else
        ( tabItem + I_PIERRE )->texture = NULL;

    ( tabItem + I_ROCHE )->id = I_ROCHE;
    ( tabItem + I_ROCHE )->nomItem = "roche";
    ( tabItem + I_ROCHE )->stack = 40;
    ( tabItem + I_ROCHE )->posable = ROCHE;
    if ( renderer ) {
        creation_chemin("data/Image/Roche_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_ROCHE )->texture);
        free(chemin);
    } else
        ( tabItem + I_ROCHE )->texture = NULL;

    ( tabItem + I_SABLE )->id = I_SABLE;
    ( tabItem + I_SABLE )->nomItem = "sable";
    ( tabItem + I_SABLE )->stack = 50;
    ( tabItem + I_SABLE )->posable = SABLE;
    if ( renderer ) {
        creation_chemin("data/Image/Sable_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_SABLE )->texture);
        free(chemin);
    } else
        ( tabItem + I_SABLE )->texture = NULL;

    ( tabItem + I_GRAVIER )->id = I_GRAVIER;
    ( tabItem + I_GRAVIER )->nomItem = "gravier";
    ( tabItem + I_GRAVIER )->stack = 50;
    ( tabItem + I_GRAVIER )->posable = GRAVIER;
    ( tabItem + I_GRAVIER )->texture = NULL;

    ( tabItem + I_BRIQUE )->id = I_BRIQUE;
    ( tabItem + I_BRIQUE )->nomItem = "brique";
    ( tabItem + I_BRIQUE )->stack = 30;
    ( tabItem + I_BRIQUE )->posable = BRIQUE;
    ( tabItem + I_BRIQUE )->texture = NULL;

    ( tabItem + I_BOIS )->id = I_BOIS;
    ( tabItem + I_BOIS )->nomItem = "bois brut";
    ( tabItem + I_BOIS )->stack = 40;
    ( tabItem + I_BOIS )->posable = BOIS;
    if ( renderer ) {
        creation_chemin("data/Image/Bois_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_BOIS )->texture);
        free(chemin);
    } else
    ( tabItem + I_BOIS )->texture = NULL;

    ( tabItem + I_POUSSE_ARBRE )->id = I_POUSSE_ARBRE;
    ( tabItem + I_POUSSE_ARBRE )->nomItem = "pousse d'arbre";
    ( tabItem + I_POUSSE_ARBRE )->stack = 50;
    ( tabItem + I_POUSSE_ARBRE )->posable = AIR;
    if ( renderer ) {
        creation_chemin("data/Image/Pousse_arbre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_POUSSE_ARBRE )->texture);
        free(chemin);
    } else
    ( tabItem + I_POUSSE_ARBRE )->texture = NULL;

    ( tabItem + I_POMME )->id = I_POMME;
    ( tabItem + I_POMME )->nomItem = "pomme";
    ( tabItem + I_POMME )->stack = 50;
    ( tabItem + I_POMME )->posable = AIR;
    if ( renderer ) {
        creation_chemin("data/Image/Pomme_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_POMME )->texture);
        free(chemin);
    } else
    ( tabItem + I_POMME )->texture = NULL;

    ( tabItem + I_BOULE_NEIGE )->id = I_BOULE_NEIGE;
    ( tabItem + I_BOULE_NEIGE )->nomItem = "boule de neige";
    ( tabItem + I_BOULE_NEIGE )->stack = 75;
    ( tabItem + I_BOULE_NEIGE )->posable = AIR;
    if ( renderer ) {
        creation_chemin("data/Image/Boule_de_neige_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_BOULE_NEIGE )->texture);
        free(chemin);
    } else
        ( tabItem + I_BOULE_NEIGE )->texture = NULL;
    
    ( tabItem + I_SILEX )->id = I_SILEX;
    ( tabItem + I_SILEX )->nomItem = "silex";
    ( tabItem + I_SILEX )->stack = 75;
    ( tabItem + I_SILEX )->posable = AIR;
    ( tabItem + I_SILEX )->texture = NULL;

    ( tabItem + I_MINERAI_FER )->id = I_MINERAI_FER;
    ( tabItem + I_MINERAI_FER )->nomItem = "minerais de fer";
    ( tabItem + I_MINERAI_FER )->stack = 25;
    ( tabItem + I_MINERAI_FER )->posable = MINERAI_FER;
    if ( renderer ) {
        creation_chemin("data/Image/Fer_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_MINERAI_FER )->texture);
        free(chemin);
    } else
        ( tabItem + I_MINERAI_FER )->texture = NULL;

    ( tabItem + I_MINERAI_CUIVRE )->id = I_MINERAI_CUIVRE;
    ( tabItem + I_MINERAI_CUIVRE )->nomItem = "minerais de cuivre";
    ( tabItem + I_MINERAI_CUIVRE )->stack = 25;
    ( tabItem + I_MINERAI_CUIVRE )->posable = MINERAI_CUIVRE;
    if ( renderer ) {
        creation_chemin("data/Image/Cuivre_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_MINERAI_CUIVRE )->texture);
        free(chemin);
    } else
        ( tabItem + I_MINERAI_CUIVRE )->texture = NULL;

    ( tabItem + I_MINERAI_ARGENT )->id = I_MINERAI_ARGENT;
    ( tabItem + I_MINERAI_ARGENT )->nomItem = "minerais de argent";
    ( tabItem + I_MINERAI_ARGENT )->stack = 25;
    ( tabItem + I_MINERAI_ARGENT )->posable = MINERAI_ARGENT;
    if ( renderer ) {
        creation_chemin("data/Image/Argent_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_MINERAI_ARGENT )->texture);
        free(chemin);
    } else
        ( tabItem + I_MINERAI_ARGENT )->texture = NULL;

    ( tabItem + I_MINERAI_OR )->id = I_MINERAI_OR;
    ( tabItem + I_MINERAI_OR )->nomItem = "minerais de cuivre";
    ( tabItem + I_MINERAI_OR )->stack = 25;
    ( tabItem + I_MINERAI_OR )->posable = MINERAI_ARGENT;
    if ( renderer ) {
        creation_chemin("data/Image/Or_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_MINERAI_OR )->texture);
        free(chemin);
    } else
        ( tabItem + I_MINERAI_OR )->texture = NULL;

    ( tabItem + I_CHARBON )->id = I_CHARBON;
    ( tabItem + I_CHARBON )->nomItem = "charbon";
    ( tabItem + I_CHARBON )->stack = 50;
    ( tabItem + I_CHARBON )->posable = AIR;
    if ( renderer ) {
        creation_chemin("data/Image/Charbon_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_CHARBON )->texture);
        free(chemin);
    } else
        ( tabItem + I_CHARBON )->texture = NULL;

    ( tabItem + I_DIAMAND )->id = I_DIAMAND;
    ( tabItem + I_DIAMAND )->nomItem = "diamant";
    ( tabItem + I_DIAMAND )->stack = 25;
    ( tabItem + I_DIAMAND )->posable = DIAMAND;
    if ( renderer ) {
        creation_chemin("data/Image/Diamant_150_150.png", &chemin);
        Create_IMG_Texture(renderer, chemin, &( tabItem + I_DIAMAND )->texture);
        free(chemin);
    } else
        ( tabItem + I_DIAMAND )->texture = NULL;

    ( tabItem + I_END )->id = I_END;
    ( tabItem + I_END )->nomItem = "end";
    ( tabItem + I_END )->stack = 0;
    ( tabItem + I_END )->posable = AIR;
    ( tabItem + I_END )->texture = NULL;
    
    /*free(chemin);*/
    SDL_FreeSurface(surface);
}
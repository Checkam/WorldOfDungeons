#include <item.h> /* #include <block.h> */

/* rand : 0 - 32767 */

t_block_drop *tabItemDrop = NULL;
t_item_type *tabItem = NULL;

uint8_t init_item() {

    if ( tabItemDrop )
        return 1;

    uint16_t i;

    tabItemDrop = malloc( sizeof( t_block_drop ) * NB_BLOCK );

    for ( i = 0 ; i < NB_BLOCK ; i++ ) {

        ( tabItemDrop + i )->id = i;
        ( tabItemDrop + i )->drop = NULL; /* aka aucun drop */
    }

    default_item_drop();

    for ( i = 0 ; i != I_END ; i++ ); /* comptage du nombre d'item */

    tabItem = malloc( sizeof( t_item_type ) * i );

<<<<<<< HEAD
    /* air */
    tabItemDrop + AIR
=======
    return 0;
}

void exit_item() {

    free( ( tabItemDrop + HERBE )->drop);
    free( ( tabItemDrop + TERRE )->drop);
    free( ( tabItemDrop + SABLE )->drop);
    free( ( tabItemDrop + FEUILLE )->drop);
    free( ( tabItemDrop + BOIS )->drop);
    free( ( tabItemDrop + ROCHE )->drop);
    free( ( tabItemDrop + NEIGE )->drop);
    free( ( tabItemDrop + DIAMAND )->drop);
    free( ( tabItemDrop + GRAVIER )->drop);

    free(tabItemDrop);
    tabItemDrop = NULL;
}

static void default_item_drop () {
    /* pour l'instant ici, ce sera fait dans des fichiers json de tib a l'avenir */

    /* AIR */
    /* rien a change car aucun drop donc pointeur drop a NULL */


    /* HERBE */
    ( tabItemDrop + HERBE )->drop = malloc( sizeof(t_liste_drop) * 1 );
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


    /* TERRE */
    ( tabItemDrop + TERRE )->drop = malloc( sizeof(t_liste_drop) * 1 );

    ( tabItemDrop + HERBE )->drop->item = I_TERRE;
    ( tabItemDrop + HERBE )->drop->nombre = 1;
    ( tabItemDrop + HERBE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + HERBE )->drop->info = 0;
    ( tabItemDrop + HERBE )->drop->pourMille = 1000;


    /* EAU */


    /* SABLE */
    ( tabItemDrop + SABLE )->drop = malloc( sizeof(t_liste_drop) * 1 );

    ( tabItemDrop + SABLE )->drop->item = I_SABLE;
    ( tabItemDrop + SABLE )->drop->nombre = 1;
    ( tabItemDrop + SABLE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + SABLE )->drop->info = 0;
    ( tabItemDrop + SABLE )->drop->pourMille = 1000;


    /* FEUILLE */
    ( tabItemDrop + FEUILLE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + FEUILLE )->drop->item = I_POUSSE_ARBRE;
    ( tabItemDrop + FEUILLE )->drop->nombre = 1;
    ( tabItemDrop + FEUILLE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + FEUILLE )->drop->info = 0;
    ( tabItemDrop + FEUILLE )->drop->pourMille = 150; /* 15% de chance de drop */

    ( tabItemDrop + FEUILLE )->drop->item = I_POMME;
    ( tabItemDrop + FEUILLE )->drop->nombre = 1;
    ( tabItemDrop + FEUILLE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + FEUILLE )->drop->info = 0;
    ( tabItemDrop + FEUILLE )->drop->pourMille = 50; /* 5% de chance de drop */


    /* BOIS */
    ( tabItemDrop + BOIS )->drop = malloc( sizeof(t_liste_drop) * 1 );

    ( tabItemDrop + BOIS )->drop->item = I_BOIS;
    ( tabItemDrop + BOIS )->drop->nombre = 1;
    ( tabItemDrop + BOIS )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + BOIS )->drop->info = 0;
    ( tabItemDrop + BOIS )->drop->pourMille = 1000;


    /* ROCHE */
    ( tabItemDrop + ROCHE )->drop = malloc( sizeof(t_liste_drop) * 1 );

    ( tabItemDrop + ROCHE )->drop->item = I_PIERRE;
    ( tabItemDrop + ROCHE )->drop->nombre = 1;
    ( tabItemDrop + ROCHE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + ROCHE )->drop->info = 0;
    ( tabItemDrop + ROCHE )->drop->pourMille = 1000;


    /* NEIGE */
    ( tabItemDrop + NEIGE )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + NEIGE )->drop->item = I_BOULE_NEIGE;
    ( tabItemDrop + NEIGE )->drop->nombre = 1;
    ( tabItemDrop + NEIGE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + NEIGE )->drop->info = 0;
    ( tabItemDrop + NEIGE )->drop->pourMille = 1000; /* 1 boule de neige sur */

    ( tabItemDrop + NEIGE )->drop->item = I_BOULE_NEIGE;
    ( tabItemDrop + NEIGE )->drop->nombre = 2;
    ( tabItemDrop + NEIGE )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + NEIGE )->drop->info = 0;
    ( tabItemDrop + NEIGE )->drop->pourMille = 200; /* 2 boule de neige a 20% chacune --> ~ 1.4 boule de neige par neige casse */


    /* GLACE */


    /* DIAMAND */
    ( tabItemDrop + DIAMAND )->drop = malloc( sizeof(t_liste_drop) * 1 );

    ( tabItemDrop + DIAMAND )->drop->item = I_DIAMAND;
    ( tabItemDrop + DIAMAND )->drop->nombre = 1;
    ( tabItemDrop + DIAMAND )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + DIAMAND )->drop->info = 0;
    ( tabItemDrop + DIAMAND )->drop->pourMille = 1000;

    /* GRAVIER */

    ( tabItemDrop + GRAVIER )->drop = malloc( sizeof(t_liste_drop) * 2 );

    ( tabItemDrop + GRAVIER )->drop->item = I_SILEX;
    ( tabItemDrop + GRAVIER )->drop->nombre = 1;
    ( tabItemDrop + GRAVIER )->drop->besoin = PAS_DROP_APRES_N;
    ( tabItemDrop + GRAVIER )->drop->info = 1;
    ( tabItemDrop + GRAVIER )->drop->pourMille = 50;

    ( tabItemDrop + GRAVIER )->drop->item = I_GRAVIER;
    ( tabItemDrop + GRAVIER )->drop->nombre = 1;
    ( tabItemDrop + GRAVIER )->drop->besoin = AUCUN_BESOIN;
    ( tabItemDrop + GRAVIER )->drop->info = 0;
    ( tabItemDrop + GRAVIER )->drop->pourMille = 1000;
}
>>>>>>> 5e5d356... suite du module item.h

static void default_item_type () {

    ( tabItem + I_TERRE )->nomItem = "terre";
    ( tabItem + I_TERRE )->stack = 50;
    ( tabItem + I_TERRE )->posable = NULL;
    ( tabItem + I_TERRE )->texture = NULL;

    ( tabItem + I_PIERRE )->nomItem = "pierre";
    ( tabItem + I_PIERRE )->stack = 25;
    ( tabItem + I_PIERRE )->posable = NULL;
    ( tabItem + I_PIERRE )->texture = NULL;

    ( tabItem + I_ROCHE )->nomItem = "roche";
    ( tabItem + I_ROCHE )->stack = 40;
    ( tabItem + I_ROCHE )->posable = NULL;
    ( tabItem + I_ROCHE )->texture = NULL;

    ( tabItem + I_SABLE )->nomItem = "sable";
    ( tabItem + I_SABLE )->stack = 50;
    ( tabItem + I_SABLE )->posable = NULL;
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
    ( tabItem + I_BOULE_NEIGE )->texture = NULL;

    ( tabItem + I_SILEX )->nomItem = "silex";
    ( tabItem + I_SILEX )->stack = 75;
    ( tabItem + I_SILEX )->posable = NULL;
    ( tabItem + I_SILEX )->texture = NULL;

    ( tabItem + I_DIAMAND )->nomItem = "diamand";
    ( tabItem + I_DIAMAND )->stack = 25;
    ( tabItem + I_DIAMAND )->posable = NULL;
    ( tabItem + I_DIAMAND )->texture = NULL;

    ( tabItem + I_END )->nomItem = "end";
    ( tabItem + I_END )->stack = 0;
    ( tabItem + I_END )->posable = NULL;
    ( tabItem + I_END )->texture = NULL;
}
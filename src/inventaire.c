#include <inventaire.h>

t_inventaire *create_inventaire() {

    t_inventaire *inventaire = malloc(sizeof(t_inventaire));

    #ifdef DEBUG
        assert( inventaire == NULL );
    #endif

    inventaire->inventaire = NULL;

    return inventaire;
}

void alloc_item(t_inventaire *inventaire, const uint16_t nbItem ) {

    if ( inventaire->inventaire == NULL ) {

        inventaire->inventaire = malloc(sizeof(t_inventaire_item) * nbItem);

        inventaire->nbItemMax = nbItem;
        inventaire->nbItem = 0;

        for ( uint16_t i = 0 ; i < nbItem ; i++ )
            ( (inventaire->inventaire) + i )->item = NULL;

    } else {

        inventaire->inventaire = realloc(inventaire->inventaire, sizeof(t_inventaire_item) * nbItem);

        for ( uint16_t i = inventaire->nbItemMax ; i < nbItem ; i++ )
            ( (inventaire->inventaire) + i )->item = NULL;

        inventaire->nbItemMax = nbItem;
    }

    #ifdef DEBUG
        assert ( inventaire->inventaire == NULL );
    #endif
}

void ajout_item_dans_inventaire( t_inventaire *inventaire, t_liste *listeItem ) {

    en_tete( listeItem );

    uint16_t placeLibre;
    t_liste_item *ptritem;

    #ifdef DEBUG 
        assert( listeItem == NULL || inventaire == NULL );
    #endif

    while ( !hors_liste( listeItem ) ) {

        valeur_elt( listeItem, (void **)&ptritem )

        placeLibre = 0;

        while ( (( inventaire->inventaire) + placeLibre)->item != tabItem + ( ptritem->item ) || placeLibre < inventaire->nbItemMax )

        if ( placeLibre >= inventaire->nbItemMax ) {

            placeLibre = 0;

            while ( ((inventaire->inventaire) + placeLibre)->item != NULL ) {

             placeLibre++;
            }
        }

        if ( placeLibre >= inventaire->nbItemMax ) {

            ( (inventaire->inventaire) + placeLibre )->item = tabItem + ( ptritem->item );
            ( (inventaire->inventaire) + placeLibre )->stack = ptritem->nbDrop;
            ( (inventaire->inventaire) + placeLibre )->durabilite = 
        }
    }
}

void free_inventaire( t_inventaire *inventaire ) {

    if ( inventaire->inventaire )
        free(inventaire->inventaire);
    
    if ( inventaire )
        free(inventaire);
}
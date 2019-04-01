#include <inventaire.h>

uint8_t alloc_item(t_inventaire *inventaire, const uint16_t nbItem ) {

    if ( inventaire->inventaire == NULL ) {

        inventaire->inventaire = malloc(sizeof(t_inventaire_item) * nbItem);

        inventaire->nbItem = nbItem;

        for ( uint16_t i = 0 ; i < nbItem ; i++ )
            ( (inventaire->inventaire) + i )->item = NULL;

    } else {

        t_inventaire *ptr_realloc;

        ptr_realloc = realloc(inventaire->inventaire, sizeof(t_inventaire_item) * nbItem);

        if ( inventaire->inventaire != ptr_realloc ) {

            free(inventaire->inventaire);
            (inventaire->inventaire) = ptr_realloc;
        }

        for ( uint16_t i = inventaire->nbItem ; i < nbItem ; i++ )
            ( (inventaire->inventaire) + i )->item = NULL;

        inventaire->nbItem = nbItem;
    }

    #ifdef DEBUG
        return inventaire->inventaire == NULL;
    #endif

    return 0;
}

void free_inventaire( t_inventaire *inventaire ) {

    free(inventaire->inventaire);
}
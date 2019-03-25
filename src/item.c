#include <item.h> /* #include <block.h> */
#include <liste.h>

t_block_drop *tabItemDrop;

void init_liste() {

    uint16_t nbItem, i;

    for ( nbItem = 0 ; nbItem != I_END ; nbItem++ );

    nbItem++;

    tabItemDrop = malloc( sizeof( t_block_drop ) * nbItem );

    for ( i = 0 ; i < nbItem ; i++ ) {

        ( tabItemDrop + i )->drop = malloc( sizeof( t_liste_drop ) );
    }
}
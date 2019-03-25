#include <item.h> /* #include <block.h> */

/* rand : 0 - 32767 */

t_block_drop *tabItemDrop;

void init_liste() {

    uint16_t i;

    tabItemDrop = malloc( sizeof( t_block_drop ) * NB_BLOCK );

    for ( i = 0 ; i < nbItem ; i++ ) {

        ( tabItemDrop + i )->drop = malloc( sizeof( t_liste_drop ) );
    }


}

static void default_liste_item () {

    /* air */
    tabItemDrop + AIR

}
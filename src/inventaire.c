#include <inventaire.h>
#include <unistd.h>

t_inventaire *create_inventaire() {

    t_inventaire *inventaire = malloc(sizeof(t_inventaire));

    #ifdef DEBUG
        assert( inventaire != NULL );
    #endif

    inventaire->inventaire = NULL;

    return inventaire;
}

void alloc_item(t_inventaire *inventaire, const uint16_t nbItem ) {

    if ( inventaire->inventaire == NULL ) {

        inventaire->inventaire = malloc(sizeof(t_inventaire_item) * nbItem);

        inventaire->nbItemMax = nbItem;
        inventaire->nbItem = 0;

        for ( uint16_t i = 0 ; i < nbItem ; i++ ) {

            ( (inventaire->inventaire) + i )->item = NULL;
            ( (inventaire->inventaire) + i )->stack = 0;
        }

    } else {

        inventaire->inventaire = realloc(inventaire->inventaire, sizeof(t_inventaire_item) * nbItem);

        for ( uint16_t i = inventaire->nbItemMax ; i < nbItem ; i++ ) {

            ( (inventaire->inventaire) + i )->item = NULL;
            ( (inventaire->inventaire) + i )->stack = 0;
        }

        inventaire->nbItemMax = nbItem;
    }

    #ifdef DEBUG
        assert ( inventaire->inventaire != NULL );
    #endif
}

void ajout_item_dans_inventaire( t_inventaire *inventaire, t_liste *listeItem ) {

    en_tete( listeItem );

    uint16_t placeLibre, i;
    t_liste_item *ptritem, *t = NULL;

    #ifdef DEBUG 
        assert( listeItem != NULL && inventaire != NULL );
    #endif

    printf("\n");

    /* pour tous les éléments de la liste */
    while ( !hors_liste( listeItem ) ) {

        valeur_elt( listeItem, (void **)&ptritem );

        printf("Traitement de l'element %p ...\n", ptritem);

        valeur_elt( listeItem, ( void **)&t);
        printf("\tla valeur suivante sera : %p\n", t);
        t = NULL;

        i = 0;
        placeLibre = inventaire->nbItemMax;

        /* recherche d'une place d'inventaire deja occupé par l'item que l'on souhaite mettre && que cette case ne soit pas rempli */
        while ( i < inventaire->nbItemMax ) {

            if ( ((( inventaire->inventaire) + i)->item) == (tabItem + ( ptritem->item )) && (( inventaire->inventaire) + i)->stack < (tabItem + ( ptritem->item ))->stack ) {

                placeLibre = i;
                i = inventaire->nbItemMax;
            }
            i++;
        }
        
        /* si aucune place trouvé alors recherche d'un case d'inventaire libre */
        if ( placeLibre >= inventaire->nbItemMax ) {

            placeLibre = 0;

            while ( ((inventaire->inventaire) + placeLibre)->item != NULL )
                placeLibre++;
        }

        /* si une place a été trouvé alors ajout de l'item dans l'inventaire */
        if ( placeLibre < inventaire->nbItemMax ) {

            /* cas 1 --> trop d'objet a casé pour que ca passe dans une seule case */
            if ( ((inventaire->inventaire) + placeLibre)->stack + ptritem->nbDrop > (tabItem + ( ptritem->item ))->stack ) {

                ( (inventaire->inventaire) + placeLibre )->stack = (tabItem + ( ptritem->item ))->stack;
                printf("\tnb item avant : %d\n", ptritem->nbDrop);
                ptritem->nbDrop -= (tabItem + ( ptritem->item ))->stack;
                printf("\tnb item apres : %d\n", ptritem->nbDrop);

                /*printf("\tajout de l'element %p ...\n", ptritem);*/
                ajout_droit(listeItem, (void *) ptritem);
                /*valeur_elt( listeItem, ( void *)t);
                printf("\tpositionnement sur l'element %p\n", t);
                t = NULL;*/
                precedent(listeItem);
                /*valeur_elt( listeItem, ( void *)t);
                printf("\tsecond positionnement sur l'element %p\n", t);
                t = NULL;*/

                inventaire->nbItem++;

            /* cas 2 --> tous passe dans une seule case */
            } else
                ( (inventaire->inventaire) + placeLibre )->stack += ptritem->nbDrop;

            (( (inventaire->inventaire) + placeLibre )->item) = (tabItem + ( ptritem->item ));
            ( (inventaire->inventaire) + placeLibre )->durabilite = (tabItem + ( ptritem->item ))->durabilite;

            valeur_elt( listeItem, ( void **)&t);
            printf(" ... suppression de l'element %p\n", t);
            t = NULL;
            oter_elt( listeItem, free);

            en_tete(listeItem);
        } else
            suivant(listeItem);
    }
}

void afficher_inventaire ( t_inventaire *inventaire ) {

    uint16_t i;

    printf("\n");

    for ( i = 0 ; i < inventaire->nbItemMax ; i++ )
        printf("slot %d : %p    nb : %d\n", i, (inventaire->inventaire + i)->item, (inventaire->inventaire + i)->stack );
}

void free_inventaire( t_inventaire *inventaire ) {

    if ( inventaire->inventaire )
        free(inventaire->inventaire);
    
    if ( inventaire )
        free(inventaire);
}
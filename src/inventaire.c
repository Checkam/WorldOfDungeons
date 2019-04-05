#include <inventaire.h>

SDL_Texture *bordure = NULL;
SDL_Texture *bordureSelectionne = NULL;

uint8_t nbinventairebarre;
uint16_t rectW;
SDL_Rect rect;

void inventaire_init( SDL_Renderer *renderer ) {

    #ifdef DEBUG
        assert(renderer != NULL);
    #endif

    char *chemin;

	creation_chemin("data/Image/Bordure_150_150.bmp", &chemin);	
	SDL_Surface *img = SDL_LoadBMP(chemin);
	bordure = SDL_CreateTextureFromSurface(renderer, img);

    creation_chemin("data/Image/BordureSelectionne_150_150.bmp", &chemin);
    img = SDL_LoadBMP(chemin);
    bordureSelectionne = SDL_CreateTextureFromSurface(renderer, img);

    SDL_FreeSurface(img);
    free(chemin);
} 

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
    t_liste_item *ptritem, *a;

    #ifdef DEBUG 
        assert( listeItem != NULL && inventaire != NULL );
    #endif

    printf("\n");

    /* pour tous les éléments de la liste */
    while ( !hors_liste( listeItem ) ) {

        valeur_elt( listeItem, (void **)&ptritem );

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
                a = malloc(sizeof(t_liste_item));
                a->nbDrop = ptritem->nbDrop - (tabItem + ( ptritem->item ))->stack;
                a->item = ptritem->item;    /* SOLUTION TEMPORAIRE */

                ajout_droit(listeItem, (void *) a);
                precedent(listeItem);

            /* cas 2 --> tous passe dans une seule case */
            } else
                ( (inventaire->inventaire) + placeLibre )->stack += ptritem->nbDrop;

            (( (inventaire->inventaire) + placeLibre )->item) = (tabItem + ( ptritem->item ));
            ( (inventaire->inventaire) + placeLibre )->durabilite = (tabItem + ( ptritem->item ))->durabilite;

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

void inventaire_changer_constante ( const uint8_t nbinventaire ) {

    nbinventairebarre = nbinventaire;

    rectW = ((DEFAULT_SIZE_IMG_W / 2) * ( uiScale / 100 )) / scaleW;
    rect.h = ((DEFAULT_SIZE_IMG_H / 2) * ( uiScale / 100 )) / scaleH;
    rect.x = WIDTH / 2 - ( ( rectW  / 2 ) * nbinventairebarre );
    rect.y = HEIGHT * 0.9;
}

void SDL_afficher_barre_action ( SDL_Renderer *renderer, t_inventaire *inventaire, const int8_t scroll ) {

    static int8_t selection = 0;

    selection += scroll;
    if ( selection < 0 )
        selection = nbinventairebarre - ((-selection) % (nbinventairebarre - 1));
    else if ( selection >= nbinventairebarre )
        selection = selection % nbinventairebarre;

    #ifdef DEBUG
        assert( renderer != NULL  && inventaire != NULL  && uiScale >= 50 && uiScale <= 150 && bordure != NULL && bordureSelectionne != NULL );
    #endif

    rect.w = rectW;

    for ( uint8_t i = 0 ; i < nbinventairebarre ; i++ ) {

        if ( i != selection )
            SDL_RenderCopy( renderer, bordure, NULL, &rect);
        else
            SDL_RenderCopy( renderer, bordureSelectionne, NULL, &rect);
        
        rect.x += rectW;
    }
}

void free_inventaire( t_inventaire *inventaire ) {

    if ( inventaire->inventaire ) {

        /*uint16_t i;

        for ( i = 0 ; i < inventaire->nbItemMax ; i++  )
            if ( (inventaire->inventaire + i)->item )
                free((inventaire->inventaire + i)->item);*/

        free(inventaire->inventaire);
    }
    
    if ( inventaire )
        free(inventaire);
}
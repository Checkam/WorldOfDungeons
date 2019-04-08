#include <inventaire.h>
#include <outils_SDL.h>

#include <stdlib.h>
#include <string.h>

#define CHEMIN_POLICE "data/police/pixel.ttf"

SDL_Color couleurNombre = {255, 255, 255};
SDL_Color couleurTexte = {255, 0, 0};

SDL_Texture *bordure = NULL;
SDL_Texture *bordureSelectionne = NULL;

uint8_t nbinventairebarre;
uint16_t rectX;
uint16_t rectTexteX;
SDL_Rect rect;
SDL_Rect rectTexteNombre;
SDL_Rect rectTexteItem;

char *police = NULL;

void inventaire_init( SDL_Renderer *renderer ) {

    #ifdef DEBUG
        assert(renderer != NULL);
    #endif

    char *chemin;

	creation_chemin("data/Image/Bordure_150_150.bmp", &chemin);	
	Create_IMG_Texture(renderer, chemin, &bordure);
    free(chemin);

    creation_chemin("data/Image/selecteur_inventaire.png", &chemin);
    Create_IMG_Texture(renderer, chemin, &bordureSelectionne);
    free(chemin);

    creation_chemin(CHEMIN_POLICE, &police);
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

            ( (inventaire->inventaire) + placeLibre )->item = (tabItem + ( ptritem->item ));

            if( ((inventaire->inventaire) + placeLibre)->stack + ptritem->nbDrop > (tabItem + ( ptritem->item ))->stack ){
                ptritem->nbDrop -= (tabItem + ( ptritem->item ))->stack - ((inventaire->inventaire) + placeLibre)->stack;
                ( (inventaire->inventaire) + placeLibre )->stack = (tabItem + ( ptritem->item ))->stack;
            }else{
                ( (inventaire->inventaire) + placeLibre )->stack += ptritem->nbDrop;
                oter_elt(listeItem, free);
            }

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

    rect.w = ((DEFAULT_SIZE_IMG_W / 2) * ( uiScale / 100 )) / scaleW;
    rect.h = ((DEFAULT_SIZE_IMG_H / 2) * ( uiScale / 100 )) / scaleH;
    rectX = WIDTH / 2 - ( ( rect.w  / 2 ) * nbinventairebarre );
    rect.y = /*HEIGHT - 30 - rect.h*/ 30;

    rectTexteNombre.w = rect.w / 3;
    rectTexteNombre.h = rect.h / 3;
    rectTexteX = rectX + rect.w - rectTexteNombre.w - 3;
    rectTexteNombre.y = rect.y + rect.h - rectTexteNombre.h - 3;
}

void SDL_afficher_barre_action ( SDL_Renderer *renderer, t_inventaire *inventaire, const int8_t scroll ) {

    #ifdef DEBUG
        assert( renderer != NULL  && inventaire != NULL  && uiScale >= 50 && uiScale <= 150 && bordure != NULL && bordureSelectionne != NULL );
    #endif

    static int8_t selection = 0;
    static uint8_t changement = 0;

    SDL_Texture *textureNombre = NULL;
    char texte[20];

    if ( scroll != 0 ) {

        changement = 50; /* nombre de frame pendant lequel le nom de l'item dera affiché */
        couleurTexte.a = 255;

        selection += scroll;
        if ( selection < 0 )
            selection = nbinventairebarre - ((-selection) % (nbinventairebarre - 1));
        else if ( selection >= nbinventairebarre )
            selection = selection % nbinventairebarre;
    }

    rect.x = rectX;
    rectTexteNombre.x = rectTexteX;

    if ( changement > 0 && (inventaire->inventaire + selection)->item != NULL ) {

        uint8_t nbLettres = strlen( ( inventaire->inventaire + selection )->item->nomItem );

        rectTexteItem.y = rect.h + rect.y + 5;
        rectTexteItem.h = rect.h / 3;
        rectTexteItem.x = WIDTH / 2 - nbLettres / 1.5 * rectTexteItem.h / 2;
        rectTexteItem.w = nbLettres / 1.5 * rectTexteItem.h;
        Create_Text_Texture(renderer, ( inventaire->inventaire + selection )->item->nomItem, police, 15, couleurTexte, BLENDED, &textureNombre );
        SDL_RenderCopy( renderer, textureNombre, NULL, &rectTexteItem);
        changement --;

        if ( changement < 25 )
            couleurTexte.a = changement * 255 / 25;
    }

    for ( uint8_t i = 0 ; i < nbinventairebarre ; i++ ) {

        if ( ( inventaire->inventaire + i)->item != NULL ) {

            sprintf( texte,"%d",(inventaire->inventaire + i)->stack);
            if ( ( inventaire->inventaire + i)->item->texture != NULL )
                SDL_RenderCopy( renderer, ( inventaire->inventaire + i)->item->texture, NULL, &rect );
            Create_Text_Texture(renderer, texte, police, 50, couleurNombre, BLENDED, &textureNombre );
            SDL_RenderCopy( renderer, textureNombre, NULL, &rectTexteNombre);
        }

        if ( i != selection )
            SDL_RenderCopy( renderer, bordure, NULL, &rect);
        else
            SDL_RenderCopy( renderer, bordureSelectionne, NULL, &rect);
        
        rect.x += rect.w;
        rectTexteNombre.x += rect.w;
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

    if( police )
        free(police);

    if ( bordure )
        SDL_DestroyTexture(bordure);

    if ( bordureSelectionne )
        SDL_DestroyTexture(bordureSelectionne);
}
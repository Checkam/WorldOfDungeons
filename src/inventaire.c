#include <inventaire.h>
#include <json.h>
#include <outils_SDL.h>

#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE_IMG_W 150
#define DEFAULT_SIZE_IMG_H 150

#define CHEMIN_POLICE "data/police/pixel.ttf"

SDL_Color couleurNombre = {255, 255, 255};
SDL_Color couleurTexte = {255, 0, 0};

SDL_Texture *bordure = NULL;
SDL_Texture *bordureSelectionne = NULL;
SDL_Texture *fondItem = NULL;

uint8_t nbinventairebarre;
uint16_t rectX;
uint16_t rectTexteX;
SDL_Rect barreRect;
SDL_Rect barreRectTexteNombre;
SDL_Rect barreRectTexteItem;

uint8_t maxLigne;
uint16_t rectInventaireX1;
uint16_t rectInventaireY1;
SDL_Rect rectInventaire1;

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

    creation_chemin("data/Image/Fond_item_150_150.png", &chemin);
    Create_IMG_Texture(renderer, chemin, &fondItem);
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
    t_liste_item *ptritem;

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

            while ( placeLibre < inventaire->nbItemMax && ((inventaire->inventaire) + placeLibre)->item != NULL)
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

    barreRect.w = ((DEFAULT_SIZE_IMG_W / 2.0) * ( uiScale / 100.0 )) / scaleW;
    barreRect.h = ((DEFAULT_SIZE_IMG_H / 2.0) * ( uiScale / 100.0 )) / scaleH;
    rectX = WIDTH / 2 - ( ( barreRect.w  / 2.0 ) * nbinventairebarre );
    barreRect.y = /*HEIGHT - 30 - barreRect.h*/ 30;

    barreRectTexteNombre.w = barreRect.w / 3;
    barreRectTexteNombre.h = barreRect.h / 3;
    rectTexteX = rectX + barreRect.w - barreRectTexteNombre.w - 3;
    barreRectTexteNombre.y = barreRect.y + barreRect.h - barreRectTexteNombre.h - 3;

    rectInventaire1.w = ((DEFAULT_SIZE_IMG_W * 0.6 ) * ( uiScale / 100 )) / scaleW;
    rectInventaire1.h = ((DEFAULT_SIZE_IMG_H * 0.6 ) * ( uiScale / 100 )) / scaleH;
    rectInventaireX1 = 30;
    rectInventaireY1 = 30;
    maxLigne = ( WIDTH * 0.4 - 30 ) / rectInventaire1.w;
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

    barreRect.x = rectX;
    barreRectTexteNombre.x = rectTexteX;

    if ( changement > 0 && (inventaire->inventaire + selection)->item != NULL ) {

        uint8_t nbLettres = strlen( ( inventaire->inventaire + selection )->item->nomItem );

        barreRectTexteItem.y = barreRect.h + barreRect.y + 5;
        barreRectTexteItem.h = barreRect.h / 3;
        barreRectTexteItem.x = WIDTH / 2 - nbLettres / 1.5 * barreRectTexteItem.h / 2;
        barreRectTexteItem.w = nbLettres / 1.5 * barreRectTexteItem.h;
        Create_Text_Texture(renderer, ( inventaire->inventaire + selection )->item->nomItem, police, 15, couleurTexte, BLENDED, &textureNombre );
        SDL_SetTextureAlphaMod( textureNombre, couleurTexte.a);
        SDL_RenderCopy( renderer, textureNombre, NULL, &barreRectTexteItem);
        SDL_DestroyTexture(textureNombre);
        changement --;

        if ( changement < 25 )
            couleurTexte.a = changement * 255 / 25;
    }

    for ( uint8_t i = 0 ; i < nbinventairebarre ; i++ ) {

        if ( ( inventaire->inventaire + i)->item != NULL ) {

            sprintf( texte,"%d",(inventaire->inventaire + i)->stack);
            SDL_RenderCopy( renderer, ( inventaire->inventaire + i)->item->texture, NULL, &barreRect );
            Create_Text_Texture(renderer, texte, police, 50, couleurNombre, BLENDED, &textureNombre );
            SDL_RenderCopy( renderer, textureNombre, NULL, &barreRectTexteNombre);
            SDL_DestroyTexture(textureNombre);
        }

        SDL_RenderCopy( renderer, bordure, NULL, &barreRect);
        if ( i == selection )
            SDL_RenderCopy( renderer, bordureSelectionne, NULL, &barreRect);
        
        barreRect.x += barreRect.w;
        barreRectTexteNombre.x += barreRect.w;
    }
}

void inventaire_afficher ( SDL_Renderer *renderer, t_inventaire *inventaire ) {

    #ifdef DEBUG
        assert( renderer != NULL && inventaire != NULL );
    #endif

    char texte[20];

    SDL_Texture *textureNombre = NULL;

    SDL_Rect rectNombre;
    rectNombre.w = rectInventaire1.w / 3;
    rectNombre.h = rectInventaire1.h / 3;

    rectInventaire1.x = rectInventaireX1;
    rectInventaire1.y = rectInventaireY1;

    uint16_t curs = 0;
    uint8_t j;

    while ( curs < inventaire->nbItemMax ) {
        for ( j = 0 ; j < maxLigne && curs < inventaire->nbItemMax ; j++, curs++ ) {

            SDL_RenderCopy(renderer, fondItem, NULL, &rectInventaire1);

            if ( ( inventaire->inventaire + curs )->item != NULL ) {

                rectNombre.x = rectInventaire1.x + rectInventaire1.w - rectNombre.w - 3;
                rectNombre.y = rectInventaire1.y + rectInventaire1.h - rectNombre.h - 3;

                sprintf( texte,"%d",(inventaire->inventaire + curs)->stack);
                SDL_RenderCopy(renderer, ( inventaire->inventaire + curs)->item->texture, NULL, &rectInventaire1);
                Create_Text_Texture(renderer, texte, police, 50, couleurNombre, BLENDED, &textureNombre );
                SDL_RenderCopy( renderer, textureNombre, NULL, &rectNombre);
            }

            rectInventaire1.x += rectInventaire1.w;
        }
        rectInventaire1.y += rectInventaire1.h;
        rectInventaire1.x = rectInventaireX1;
    }

    SDL_DestroyTexture(textureNombre);
}

void inventaire_enregistrer ( const char *path, t_enr_inventaire *enr_inventaire ) {

    FILE *enr = open_json( path, "inventaire", "w+");

    int nil = -1, intBuf;
    char buffer[6];

    open_json_obj(enr);

    write_json(enr, "x", &(enr_inventaire->x), "d");
    write_json(enr, "y", &(enr_inventaire->x), "d");
    write_json(enr, "nbItems", &(enr_inventaire->inventaire->nbItemMax), "d");

    for ( uint16_t i = 0 ; i < enr_inventaire->inventaire->nbItemMax ; i++ ) {

        sprintf(buffer, "%d", i);

        if ( (enr_inventaire->inventaire->inventaire + i )->item != NULL ){
            intBuf = ((enr_inventaire->inventaire->inventaire + i )->item->id);
            write_json(enr, buffer, &intBuf, "d" );
            printf("%d : %u\n", i, intBuf);
        }
        else {
            write_json(enr, buffer, &nil, "d" );
            printf("%d : nil\n", i);
        }
    }
        
    close_json_obj(enr);
}

uint8_t inventaire_recuperer ( const char *path, t_inventaire **inventaire ) {

    FILE *enr = open_json( path, "inventaire", "r");

    fstart(enr);

    /*do {

        

    } while ();*/
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